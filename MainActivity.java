package com.example.app0710807_1;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    TextView textView;
    Button Button_SET;
    Button Button_RESET;
    EditText editText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

       textView = (TextView)findViewById(R.id.textView);
       textView.setText("Hello");

       editText = (EditText)findViewById(R.id.editText) ;

       Button_SET = (Button)findViewById(R.id.button_SET);
       Button_SET.setText("SET");
       Button_SET.setOnClickListener(new View.OnClickListener(){
           @Override
           public void onClick(View v){
               textView.setText("Welcome to Android, " + editText.getText().toString());
           }
       });


        Button_RESET = (Button)findViewById(R.id.button_RESET);
        Button_RESET.setText("RESET");
        Button_RESET.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                textView.setText("Hello World!");
            }
        });


    }
}