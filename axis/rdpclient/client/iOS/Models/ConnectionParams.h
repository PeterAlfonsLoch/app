/*
 Connection Parameters abstraction

 Copyright 2013 Thincast Technologies GmbH, Author: Dorian Johnson

 This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */


#import <Foundation/Foundation.h>

@interface ConnectionParams : NSObject
{
@private
    NSMutableDictionary* _connection_params;
}

// Designated initializer.
- (id)initWithDictionary:(NSDictionary*)dict;
- (id)initWithBaseDefaultParameters;

// Getting/setting values
- (NSArray*)allKeys;
- (void)setValue:(id)value forKey:(NSString *)key;
- (id)valueForKey:(NSString*)key;
- (WINBOOL)hasValueForKey:(NSString*)key;
- (void)setInt:(int)integer forKey:(NSString*)key;
- (int)intForKey:(NSString*)key;
- (void)setBool:(WINBOOL)v forKey:(NSString*)key;
- (WINBOOL)boolForKey:(NSString*)key;
- (const char*)UTF8StringForKey:(NSString*)key;
- (NSString*)StringForKey:(NSString*)key;

- (WINBOOL)hasValueForKeyPath:(NSString*)key;
- (void)setInt:(int)integer forKeyPath:(NSString*)key;
- (int)intForKeyPath:(NSString*)key;
- (void)setBool:(WINBOOL)v forKeyPath:(NSString*)key;
- (WINBOOL)boolForKeyPath:(NSString*)key;
- (const char*)UTF8StringForKeyPath:(NSString*)key;
- (NSString*)StringForKeyPath:(NSString*)key;


- (int)intForKey:(NSString*)key with3GEnabled:(WINBOOL)enabled;
- (WINBOOL)boolForKey:(NSString*)key with3GEnabled:(WINBOOL)enabled;

@end
