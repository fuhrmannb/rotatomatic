package me.fuhrmannb.rotatomatic.client

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle

class RotatomaticActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_rotatomatic)
    }

    override fun onStart() {
        super.onStart()
        Intent(this, RotatomaticService::class.java).also { intent ->
            startService(intent)
        }
    }
}
