//----------------------
package org.cocos2dx.cpp;

public class CppBridge {
    public static int Google_Id_SignIn = 1;
    public static int Facebook_Id_SignIn = 2;
    public static native void onDidSocialSignIn(String personName, String personEmail, String personId, int index);
    public static native void onDidSocialSignOut();
}
