package lab.sodino.inotify;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;


public class MainActivity extends Activity implements OnClickListener {
	static {
		System.loadLibrary("Inotify");
	}
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        TextView txt = (TextView)findViewById(R.id.txtJni);
        txt.setText(hello());
        
        Button btn = (Button)findViewById(R.id.btnJni);
        btn.setOnClickListener(this);
    }

    native String hello();
    native void watchFile();
    
	@Override
	public void onClick(View v) {
		switch(v.getId()){
		case R.id.btnJni:
			watchFile();
			break;
		}
	}
}
