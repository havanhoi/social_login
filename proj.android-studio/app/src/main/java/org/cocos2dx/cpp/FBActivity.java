package org.cocos2dx.cpp;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.Toast;

import com.earlystart.android.monkeyjunior.R;
import com.facebook.AccessToken;
import com.facebook.CallbackManager;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
import com.facebook.GraphRequest;
import com.facebook.GraphResponse;
import com.facebook.login.LoginManager;
import com.facebook.login.LoginResult;
import com.facebook.login.widget.LoginButton;

import org.json.JSONObject;

public class FBActivity extends AppCompatActivity {
    private CallbackManager callbackManager;
    private LoginButton loginButton;
    //private TextView btnLogin;
    private String userInfo = "";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fb);


    }

    @Override
    public void onStart() {
        super.onStart();
        Log.e("Check", "Start");
        callbackManager=CallbackManager.Factory.create();

        loginButton= (LoginButton)findViewById(R.id.fbLogin);

        loginButton.setReadPermissions("public_profile", "email");

        // btnLogin= (TextView) findViewById(R.id.btnLogin);
        Bundle bundle = getIntent().getExtras();
        if(bundle.getBoolean("isSignInFB", false)) {
            AccessToken accessToken = AccessToken.getCurrentAccessToken();
            if (accessToken != null) {
                getFacebookInfo(accessToken);
            } else {
                loginButton.performClick();

                loginButton.setPressed(true);

                loginButton.invalidate();

                loginButton.registerCallback(callbackManager, mCallBack);

                loginButton.setPressed(false);

                loginButton.invalidate();
            }
            return;
        }

        if(bundle.getBoolean("isSignOutFB", false)) {
            showAlertConfirmSignout();
        }
    }

    private  void showAlertConfirmSignout() {
        AlertDialog alertDialog;
        AlertDialog.Builder builder = new AlertDialog.Builder(this);

        builder.setMessage("Do you want signout?");
        builder.setTitle("Facebook");
        builder.setPositiveButton("Ok", new DialogInterface.OnClickListener() {

            @Override
            public void onClick(DialogInterface dialog, int which) {
                // TODO Auto-generated method stub
                LoginManager.getInstance().logOut();
                didSignOut();
            }
        });
        builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {

            @Override
            public void onClick(DialogInterface dialog, int which) {
                // TODO Auto-generated method stub
                backToSceneCocos2dx();
            }
        });
        alertDialog = builder.create();
        alertDialog.show();
    }



    private void backToSceneCocos2dx(){
        Intent intent = new Intent(this,org.cocos2dx.cpp.AppActivity.class);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_TASK_ON_HOME);
        startActivity(intent);
    }

    private void getFacebookInfo(com.facebook.AccessToken token) {
        GraphRequest request = GraphRequest.newMeRequest(
                token,
                new GraphRequest.GraphJSONObjectCallback() {
                    @Override
                    public void onCompleted(
                            JSONObject object,
                            GraphResponse response) {

                        Log.e("response: ", response + "");
                        try {
                            userInfo = "";
                            userInfo += "user.id: " + object.getString("id").toString();
                            userInfo += "user.email: " + object.getString("email").toString();
                            userInfo += "user.name: " + object.getString("name").toString();

                            didSignInFB(object.getString("name").toString(), object.getString("id").toString(), object.getString("email").toString());
                            //logInfo();
                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                        //thanh cong
//                        finish();

                    }

                });
        Bundle parameters = new Bundle();
        parameters.putString("fields", "id,name,email");
        request.setParameters(parameters);
        request.executeAsync();
    }

    private void didSignOut() {
        Intent intent = new Intent(this,org.cocos2dx.cpp.AppActivity.class);
        intent.putExtra("didSignOut", true);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_TASK_ON_HOME);
        startActivity(intent);
    }

    private void didSignInFB(String userName, String userID, String userMail){
        Log.e("Facebook - ", "isSignIn: true");
        Intent intent = new Intent(this,org.cocos2dx.cpp.AppActivity.class);
        intent.putExtra("personId_FB", userID);
        intent.putExtra("personName_FB", userName);
        intent.putExtra("personEmail_FB", userMail);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_TASK_ON_HOME);
        startActivity(intent);
    }

    @Override
    protected void onResume() {
        super.onResume();



//        btnLogin.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//
//
//            }
//        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        callbackManager.onActivityResult(requestCode, resultCode, data);
    }

    private void logInfo() {
        Toast.makeText(FBActivity.this, userInfo, Toast.LENGTH_LONG).show();
    }
    private FacebookCallback<LoginResult> mCallBack = new FacebookCallback<LoginResult>() {
        @Override
        public void onSuccess(LoginResult loginResult) {
            getFacebookInfo(loginResult.getAccessToken());
        }

        @Override
        public void onCancel() {

        }

        @Override
        public void onError(FacebookException e) {

        }
    };

    //
}
