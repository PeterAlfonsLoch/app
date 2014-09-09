//
//  BlockAlertView.h
//
//

#import <UIKit/UIKit.h>

@interface BlockAlertView : NSObject {
@protected
    UIView *_view;
    NSMutableArray *_blocks;
    CGFloat _height;
    NSString *_title;
    NSString *_message;
    WINBOOL _shown;
    WINBOOL _cancelBounce;
}

+ (BlockAlertView *)alertWithTitle:(NSString *)title message:(NSString *)message;

+ (void)showInfoAlertWithTitle:(NSString *)title message:(NSString *)message;
+ (void)showErrorAlert:(NSError *)error;

- (id)initWithTitle:(NSString *)title message:(NSString *)message;

- (void)setDestructiveButtonWithTitle:(NSString *)title block:(void (^)())block;
- (void)setCancelButtonWithTitle:(NSString *)title block:(void (^)())block;
- (void)addButtonWithTitle:(NSString *)title block:(void (^)())block;

- (void)addComponents:(CGRect)frame;

- (void)show;
- (void)dismissWithClickedButtonIndex:(NSInteger)buttonIndex animated:(WINBOOL)animated;

- (void)setupDisplay;

@property (nonatomic, retain) UIImage *backgroundImage;
@property (nonatomic, readonly) UIView *view;
@property (nonatomic, readwrite) WINBOOL vignetteBackground;

@end
