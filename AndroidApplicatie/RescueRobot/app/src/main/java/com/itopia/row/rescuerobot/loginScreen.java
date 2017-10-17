package com.itopia.row.rescuerobot;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.view.View;
import android.widget.Toast;

import static java.lang.Integer.parseInt;

public class loginScreen extends AppCompatActivity {
    EditText address, port;
    Button buttonConnect, buttonClear;


    public static String serverIp;
    public static int serverPort;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.login);
        getSupportActionBar().hide();

        address = (EditText) findViewById(R.id.address);
        port = (EditText) findViewById(R.id.port);
        buttonConnect = (Button) findViewById(R.id.connect);
        buttonClear = (Button) findViewById(R.id.clear);


        buttonConnect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (address.getText().toString().equals("") || port.getText().toString().equals("")) {
                    AlertDialog alertDialog = new AlertDialog.Builder(loginScreen.this).create();
                    alertDialog.setTitle("Niet alle velden zijn ingevuld");
                    alertDialog.setMessage("Vul alle velden in om verder te gaan");
                    alertDialog.setButton(AlertDialog.BUTTON_NEUTRAL, "OK", new DialogInterface.OnClickListener() {
                        public void onClick(DialogInterface dialog, int which) {
                            dialog.dismiss();
                        }
                    });
                    alertDialog.show();
                }else {
                    serverIp = address.getText().toString();
                    serverPort = parseInt(port.getText().toString());
                    
                    startActivity(new Intent(v.getContext(), MainActivity.class));
                    Toast.makeText(getApplicationContext(), "Connecting to Raspberry Pi", Toast.LENGTH_SHORT).show();

                }
            }


        });

        buttonClear.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                address.setText("");
                port.setText("");

            }
        });
    }

}