package com.example.qr_zxing_test2;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends Activity {
	Button b1;
	static String contents;

	public static final int REQUEST_CODE = 1;

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		b1 = (Button) findViewById(R.id.button1);
		b1.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				/*
				 * Intent intent = new
				 * Intent("com.google.zxing.client.android.SCAN");
				 * intent.putExtra
				 * ("com.google.zxing.client.android.SCAN.SCAN_MODE",
				 * "QR_CODE_MODE"); startActivityForResult(intent, 0);
				 */
				Intent intent = new Intent(
						"com.google.zxing.client.android.SCAN");
				intent.putExtra("SCAN_MODE", "QR_CODE_MODE");
				startActivityForResult(intent, 0);

			}
		});
	}

	public void onActivityResult(int requestCode, int resultCode, Intent intent) {
		if (requestCode == 0) {
			if (resultCode == RESULT_OK) {
				contents = intent.getStringExtra("SCAN_RESULT");
				String format = intent.getStringExtra("SCAN_RESULT_FORMAT");
				Log.i("Barcode Result", contents);
			//	Intent i1 = new Intent(MainActivity.this, webclass.class);
				//startActivity(i1);
				// Handle successful scan
			} else if (resultCode == RESULT_CANCELED) {
				// Handle cancel
				Log.i("Barcode Result", "Result canceled");
			}
		}
	}
}
