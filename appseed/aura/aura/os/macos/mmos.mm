
#import "framework.h"
#include <CoreFoundation/CoreFoundation.h>

void macos_desktop_image_changed();
bool mm2_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz);

@implementation mmos

+ (id)get
{
   
   static mmos * s_mmos = NULL;
   
   if(s_mmos == NULL)
   {
      
      s_mmos = ([[[self alloc] init] autorelease]);
      
      s_mmos->m_ppszWallpaper = NULL;
      
      s_mmos->m_llWallpaper = 0;
      
      
      s_mmos->m_iIcon = 0;
      
      
      [s_mmos monitorWallpaper];
      
      [s_mmos monitorIconForFile];
      
      //-(void)awakeFromNib
//      {
//         [[[NSWorkspace sharedWorkspace] notificationCenter]
//          addObserver:s_mmos
//          selector:@selector(applicationActivity:)
//          name:NSWorkspaceDidActivateApplicationNotification 
//          object:nil];
//      }
//      [[NSDistributedNotificationCenter defaultCenter] addObserver:s_mmos
//                                                          selector:@selector(desktopImageChanged:)
//                                                              name:@"com.apple.desktop"
//                                                            object:nil];
   }
   
   return s_mmos;
   
}

- (void)get_user_wallpaper:(void **)charpp forScreen:(NSScreen *) s;
{
   
   char ** ppsz = (char **) charpp;
   
   NSURL * purl = [[NSWorkspace sharedWorkspace] desktopImageURLForScreen:s];
   
   if(purl == NULL)
   {
      
      *ppsz = NULL;
      
   }
   else
   {
   
      *ppsz = strdup([[purl absoluteString] UTF8String]);
                     
   }
   
}

- (void)get_user_wallpaper:(void *)charppp getCount:(void *) llp
{
   
   

   long long * pll = (long long *) llp;

   NSArray<NSScreen *> * screenArray = [NSScreen screens];

   *pll = [screenArray count];
   
   char ** p = (char **) malloc(*pll * sizeof(char*));
   
   
   char *** ppsz = (char ***) charppp;
   
   *ppsz = p;

   for (int i = 0; i < *pll; i++)
   {
   
      NSScreen * screen = [screenArray objectAtIndex: i];
      
      [self get_user_wallpaper: (void **)&p[i] forScreen:screen];
   
   }
   
}


- (void)desktopImageChanged:(NSNotification *)notification
{
   
   macos_desktop_image_changed();
   
}

-(void)applicationActivity:(NSNotification *)notification
{
   NSRunningApplication *app = [[notification userInfo] objectForKey:@"NSWorkspaceApplicationKey"];
   if([app.localizedName isEqualToString:@"ScreenSaverEngine"])
   {
      
      macos_desktop_image_changed();
      // Your code here
   }
}

-(void)monitorWallpaper
{
   
   NSRunLoop* myRunLoop = [NSRunLoop mainRunLoop];
   
   
   
   NSMethodSignature *sgn = [self methodSignatureForSelector:@selector(deferWallpaper:)];
   NSInvocation *inv = [NSInvocation invocationWithMethodSignature: sgn];
   [inv setTarget: self];
   [inv setSelector:@selector(deferWallpaper:)];
   
   NSTimer *t = [NSTimer timerWithTimeInterval: 0.1
                                    invocation:inv
                                       repeats:YES];
   
   [myRunLoop addTimer:t forMode:NSDefaultRunLoopMode];
   
}
-(void)deferWallpaper:(NSTimer *)timer
{
   
   char ** ppsz = NULL;
   
   long long ll;
   
   [self get_user_wallpaper: (void *) &ppsz getCount: (void *) &ll];
   
   char ** ppszOld = self->m_ppszWallpaper;
   
   long long llOld = self->m_llWallpaper;
   
   if(ppsz != NULL)
   {
      
      self->m_ppszWallpaper = ppsz;
      
      self->m_llWallpaper = ll;
      
      for(long long i = 0; i < llOld; i++)
      {
         
         free(ppszOld[i]);
         
      }
      
      free(ppszOld);
      
      
   }

}
-(void)monitorIconForFile
{
   
   NSRunLoop* myRunLoop = [NSRunLoop mainRunLoop];
   
   
   
   NSMethodSignature *sgn = [self methodSignatureForSelector:@selector(deferIconForFile:)];
   NSInvocation *inv = [NSInvocation invocationWithMethodSignature: sgn];
   [inv setTarget: self];
   [inv setSelector:@selector(deferIconForFile:)];
   
   NSTimer *t = [NSTimer timerWithTimeInterval: 0.1
                                    invocation:inv
                                       repeats:YES];
   
   [myRunLoop addTimer:t forMode:NSDefaultRunLoopMode];
   
}
-(void)deferIconForFile:(NSTimer *)timer
{

   if(self->m_iIcon != 1)
   {
      
      return;
      
   }
      
   if(self->m_pszIcon == NULL)
   {
      
      self->m_iIcon = 0;
      
      return;
      
   }
   
   mm2_get_file_image(self->m_picon, self->m_cxIcon, self->m_cyIcon, self->m_iScanIcon, self->m_pszIcon);
   
   self->m_iIcon = 0;
   
}
@end




bool mm1a_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz)
{
   
   mmos * os = [mmos get];
   
   if(os->m_iIcon == 0)
   {
      os->m_pszIcon = psz;
      os->m_picon = pcr;
      os->m_cxIcon = cx;
      os->m_cyIcon = cy;
      os->m_iScanIcon = iScan;
      os->m_iIcon = 1;
      while(os->m_iIcon != 0)
      {
         
         Sleep(5);
         
      }
   }
      
   
   return true;
      
}


void ns_set_this_process_binary_default_browser()
{
   
   CFBundleRef bundle = CFBundleGetMainBundle();
   
   CFURLRef url = CFBundleCopyBundleURL(bundle);
   
   LSRegisterURL(url, true);
   
   CFStringRef identifier = CFBundleGetIdentifier(bundle);
   
   LSSetDefaultHandlerForURLScheme(CFSTR("http"), identifier);
   
}




void ns_create_alias(const char * pszTarget, const char * pszSource)
{
   NSString * strTarget = [[NSString alloc]initWithUTF8String:pszTarget];
   NSString * strSource = [[NSString alloc]initWithUTF8String:pszSource];
   
   [[NSFileManager defaultManager ] createSymbolicLinkAtPath: strTarget withDestinationPath: strSource error:nil];
}
