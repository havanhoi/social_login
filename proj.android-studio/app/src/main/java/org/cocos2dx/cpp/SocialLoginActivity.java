package org.cocos2dx.cpp;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Toast;

import com.earlystart.android.monkeyjunior.R;

public class SocialLoginActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_social_login);
    }

//    public void quaylaiMain() {
//        Log.e("SocialLoginActivity", "Quay lai main scene");
//    }

    public void quaylaiMain(View v)
    {
        Intent intent = new Intent(this,org.cocos2dx.cpp.AppActivity.class);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_TASK_ON_HOME);
        startActivity(intent);
    }

}
