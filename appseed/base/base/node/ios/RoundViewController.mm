//
//  RoundViewController.m
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 14/05/14.
//
//

#import "ios_mm.h"

@interface RoundViewController ()

@end

@implementation RoundViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
   
   [super viewDidLoad];
   
   // Do any additional setup after loading the view.
   
   childContentView.frame = self.view.frame;
   
   childContentView.delegate = self;
   
   //childContentView.text = @"Lorem Ipsum";
   
}


-(BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
   
   [childContentView on_text : text ];
   
   return FALSE;
   
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/


-(void) viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(id )coordinator
{
   
   try
   {
      
      CGRect rect;
      
      rect.origin.x = 0;
      rect.origin.y = 0;
      rect.size = size;
      
      m_pwindow->m_pwindow->round_window_resized(rect);
      
   }
   catch (...)
   {
      
      
      
   }
   
   //      NSRect rect = [self frame];
   //
   //      rect.origin.y        = [[NSScreen mainScreen] frame ].size.height - (rect.origin.y + rect.size.height);
   //
   //      m_pwindow->round_window_resized(rect);
   
}

@end
