/****************************************************************************
Copyright (c) 2015 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import com.google.android.gms.auth.api.signin.GoogleSignInOptions;

import org.cocos2dx.lib.Cocos2dxActivity;


public class AppActivity extends Cocos2dxActivity {
    static AppActivity _ac = null;
    static String TAG = "AppActivity";



    @Override
    protected void onCreate(final Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        GoogleSignInOptions gso = new GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_SIGN_IN)
                .requestEmail()
                .build();
        Log.e("AppActivity", "Vao day roi");

        String infoUser = "";

        Bundle bundle = getIntent().getExtras();
        if(bundle != null) {
            if(bundle.getString("personId") != null) {
                infoUser += "personId: " + bundle.getString("personId").toString();
                infoUser += " - personName: " + bundle.getString("personName").toString();
                infoUser += " - personEmail: " + bundle.getString("personEmail").toString();

                String personName = bundle.getString("personName").toString();
                String personEmail = bundle.getString("personEmail").toString();
                String personId = bundle.getString("personId").toString();

                CppBridge.onDidGoogleSignIn(personName, personEmail, personId);
                //Toast.makeText(this.getBaseContext(), infoUser, Toast.LENGTH_SHORT).show();
            }

            if (bundle.getBoolean("didSignOut", false)){
                Log.e("didSignOut", " didSignOut");
                CppBridge.onDidGoogleSignOut();
            }
        }


        _ac = this;
    }

    public static void onGoogleSignIn() {
        Log.e(TAG, "=====> loginAction");
        _ac.signInAction();
    }

    public static void onGoogleSignOut() {
        Log.e(TAG, "=====> loginAction");
        _ac.signOutAction();
    }

    public void signInAction() {
        Log.e(TAG, "=====> openLogin");
        Intent intent = new Intent(this,org.cocos2dx.cpp.SocialLoginActivity.class);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_TASK_ON_HOME);
        intent.putExtra("isSignIn", true);
        startActivity(intent);
    }


    public void signOutAction() {
        Log.e(TAG, "=====> openLogin");
        Intent intent = new Intent(this,org.cocos2dx.cpp.SocialLoginActivity.class);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_TASK_ON_HOME);
        intent.putExtra("isSignOut", true);
        startActivity(intent);
    }
}

