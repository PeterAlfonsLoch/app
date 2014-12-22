//
//  RoundViewController.m
//  base
//
//  Created by Carlos Gustavo Cecyn Lundgren on 14/05/14.
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
   
   childContentView.text = @"Lorem Ipsum";
   
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

@end
