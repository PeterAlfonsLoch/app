/**************************************************************************************************
	$Id: rr.c,v 1.38 2005/12/08 17:22:59 bboy Exp $

	Copyright (C) 2002-2005  Don Moore <bboy@bboy.net>

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at Your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**************************************************************************************************/

#include "StdAfx.h"

/* Make this nonzero to enable debugging for this source file */
#define	DEBUG_RR	1

#if DEBUG_ENABLED && DEBUG_RR
/* Strings describing the datasections */
char *datasection_str[] = { "QUESTION", "ANSWER", "AUTHORITY", "ADDITIONAL" };
#endif


/**************************************************************************************************
	RRLIST_FREE
**************************************************************************************************/
void
rrlist_free(RRLIST *list)
{
	if (list)
	{
		register RR *p, *tmp;

		for (p = list->head; p; p = tmp)
		{
			tmp = p->next;
			switch (p->rrtype)
			{
				case DNS_RRTYPE_SOA:
					mydns_soa_free(p->rr);
					break;
				case DNS_RRTYPE_RR:
					mydns_rr_free(p->rr);
					break;
			}
			Free(p);
		}
		memset(list, 0, sizeof(RRLIST));
	}
}
/*--- rrlist_free() -----------------------------------------------------------------------------*/


/**************************************************************************************************
	RRDUP
	Returns nonzero if the resource record specified is duplicated in the provided list.
**************************************************************************************************/
static int
rrdup(RRLIST *list, dns_rrtype_t rrtype, uint32_t id)
{
	register RR *r;

	if (list && id)												/* Ignore (fake) RRs with ID 0 */
		for (r = list->head; r; r = r->next)
			if (r->rrtype == rrtype && r->id == id)
				return (1);
	return (0);
}
/*--- rrdup() -----------------------------------------------------------------------------------*/


/**************************************************************************************************
	RRLIST_ADD
	Adds a resource record to the section specified.
	The function will make a copy of `rr', so the caller should free their copy if desired.
**************************************************************************************************/
void
rrlist_add(
	TASK *t,							/* The task to add a record to */
	datasection_t ds,				/* Add `rr' to this data section */
	dns_rrtype_t rrtype,			/* The type of resource record being added */
	void *rr,						/* The resource record to add */
	char *name						/* Name to send with reply */
)
{
	RRLIST *list = NULL;
	RR *prrNew;
	uint32_t id = 0;
	register char *s, *d;

	/* Remove erroneous empty labels in 'name' if any exist */
	if (name)
	{
		for (s = d = name; *s; s++)
			if (s[0] == '.' && s[1] == '.')
				*d++ = *s++;
			else
				*d++ = *s;
		*d = '\0';
	}

#if DN_COLUMN_NAMES
	if (rrtype == DNS_RRTYPE_RR && ds == ADDITIONAL)
	{
		MYDNS_RR *r = (MYDNS_RR *)rr;
		if (!strcmp(r->name, "*"))
			return;
	}
#endif

#if DEBUG_ENABLED && DEBUG_RR
	{
		switch (rrtype)
		{
			case DNS_RRTYPE_SOA:
				{
					MYDNS_SOA *soa = (MYDNS_SOA *)rr;
					Debug("%s: RRLIST_ADD: %s (id=%u) (%s) (`%s')", desctask(t),
							datasection_str[ds], soa->id, soa->origin, name);
				}
				break;

			case DNS_RRTYPE_RR:
				{
					MYDNS_RR *r = (MYDNS_RR *)rr;
					Debug("%s: RRLIST_ADD: %s (id=%u) (name='%s',qtype='%s',data='%s') (`%s')", desctask(t),
							datasection_str[ds], r->id,
							(char *)(strlen(r->name) ? r->name : (char *)""),
							mydns_qtype_str(r->type), r->data, name);
				}
				break;
		}
	}
#endif

	/* Check to make sure this isn't a duplicate */
	switch (rrtype)
	{
		case DNS_RRTYPE_SOA:		id = ((MYDNS_SOA *)rr)->id; break;
		case DNS_RRTYPE_RR:		id = ((MYDNS_RR *)rr)->id; break;
	}

	/* Check only the current section */
	switch (ds)
	{
		case QUESTION:
			break;

		case ANSWER:
			list = &t->an;
			if (rrdup(&t->an, rrtype, id))
			{
#if DEBUG_ENABLED && DEBUG_RR
				Debug("%s: Duplicate record, ignored", desctask(t));
#endif
				return;
			}
			break;

		case AUTHORITY:
			list = &t->ns;
			if (rrdup(&t->ns, rrtype, id) || rrdup(&t->an, rrtype, id))
			{
#if DEBUG_ENABLED && DEBUG_RR
				Debug("%s: Duplicate record, ignored", desctask(t));
#endif
				return;
			}
			break;

		case ADDITIONAL:
			list = &t->ar;
			if (rrdup(&t->ar, rrtype, id) || rrdup(&t->an, rrtype, id))
			{
#if DEBUG_ENABLED && DEBUG_RR
				Debug("%s: Duplicate record, ignored", desctask(t));
#endif
				return;
			}
			break;
	}

	if (!(prrNew = (RR*)malloc(sizeof(RR))))
		Err(_("out of primitive::memory"));
	prrNew->rrtype = rrtype;
	switch (prrNew->rrtype)
	{
		case DNS_RRTYPE_SOA:
			prrNew->rr = mydns_soa_dup((MYDNS_SOA *)rr, 0);
			if (!ignore_minimum && (((MYDNS_SOA *)prrNew->rr)->ttl < t->minimum_ttl))
				((MYDNS_SOA *)prrNew->rr)->ttl = t->minimum_ttl;
			break;

		case DNS_RRTYPE_RR:
			prrNew->rr = mydns_rr_dup((MYDNS_RR *)rr, 0);
			/* Some RR types need to be flagged for sorting */
			switch (((MYDNS_RR *)rr)->type)
			{
				case DNS_QTYPE_A:
				case DNS_QTYPE_AAAA:
					list->a_records++;
					break;

				case DNS_QTYPE_MX:
					list->mx_records++;
					break;

				case DNS_QTYPE_SRV:
					list->srv_records++;
					break;

				default:
					break;
			}

			/* Keep track of the lowest TTL found (for cache) */
			if (!ignore_minimum && (((MYDNS_RR *)prrNew->rr)->ttl < t->minimum_ttl))
				((MYDNS_RR *)prrNew->rr)->ttl = t->minimum_ttl;

			/* Don't cache this reply if the TTL for this record is 0 */
			if (((MYDNS_RR *)prrNew->rr)->ttl == 0)
				t->reply_cache_ok = 0;

			break;
	}

	prrNew->id = id;
	prrNew->offset = 0;
	prrNew->sort_level = t->sort_level;
	prrNew->sort1 = 0;
	prrNew->sort2 = 0;
	strncpy((char *) prrNew->name, name, sizeof(prrNew->name)-1);
	prrNew->next = NULL;
	if (!list->head)
		list->head = list->tail = prrNew;
	else
	{
		list->tail->next = prrNew;
		list->tail = prrNew;
	}
	list->size++;
}
/*--- rrlist_add() ------------------------------------------------------------------------------*/

/* vi:set ts=3: */
