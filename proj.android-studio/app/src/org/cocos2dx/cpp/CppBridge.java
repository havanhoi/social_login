//----------------------
package org.cocos2dx.cpp;

public class CppBridge {
    public static native void onDidGoogleSignIn(String personName, String personEmail, String personId);
    public static native void onDidGoogleSignOut();
}
