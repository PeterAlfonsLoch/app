
#import "framework.h"

void macos_desktop_image_changed();

@implementation mmos

+ (id)get
{
   
   static mmos * s_mmos = NULL;
   
   if(s_mmos == NULL)
   {
      
      s_mmos = ([[[self alloc] init] autorelease]);
      
      s_mmos->m_ppszWallpaper = NULL;
      
      s_mmos->m_llWallpaper = 0;
      
      [s_mmos monitorWallpaper];
      
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
@end
