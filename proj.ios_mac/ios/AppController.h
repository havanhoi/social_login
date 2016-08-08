#import <UIKit/UIKit.h>
#define XAppDelegate ((AppController*)[[UIApplication sharedApplication] delegate])

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;


- (void) onGooglePlusSignIn;
- (void) onGooglePlusSignOut;
- (void) onFBSignIn;
- (void) onFBSignOut;

@end

