#import <UIKit/UIKit.h>
#define XAppDelegate ((AppController*)[[UIApplication sharedApplication] delegate])

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    int countFBLogin;
}

@property(nonatomic, readonly) RootViewController* viewController;


- (void) onGoogleSignIn;
- (void) onGoogleSignOut;
- (void) onFBSignIn;
- (void) onFBSignOut;
@end

