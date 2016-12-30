@interface mmos : NSObject
{
@public  char ** m_ppszWallpaper;
@public   long long m_llWallpaper;

}

+ (id)get;

- (void)get_user_wallpaper:(void **)charpp forScreen:(NSScreen *) s;

- (void)get_user_wallpaper:(void *)charppp getCount:(void *) pll;

- (void)desktopImageChanged:(NSNotification *)notification;

- (void)applicationActivity:(NSNotification *)notification;

- (void)monitorWallpaper;

- (void)deferWallpaper:(NSTimer *)timer;
@end

