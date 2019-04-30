package me.fuhrmannb.rotatomatic.client

import android.app.Service
import android.content.Intent
import android.os.IBinder
import android.view.OrientationEventListener
import android.widget.Toast
import android.hardware.SensorManager
import android.util.Log
import com.koushikdutta.async.callback.CompletedCallback
import com.koushikdutta.async.http.server.AsyncHttpServer
import com.koushikdutta.async.AsyncServer
import com.koushikdutta.async.http.WebSocket


class RotatomaticService : Service() {

    private lateinit var mOrientationListener: OrientationEventListener
    private var mSockets = ArrayList<WebSocket>()

    private var httpServer = AsyncHttpServer().also {
        it.errorCallback = CompletedCallback { ex ->
            Log.e("WebSocket", "An error occurred", ex)
        }

        it.websocket("/rotation") { webSocket, _ ->
            mSockets.add(webSocket)

            // Use this to clean up any references to your websocket
            webSocket.closedCallback = CompletedCallback { ex ->
                try {
                    if (ex != null)
                        Log.e("WebSocket", "An error occurred", ex)
                } finally {
                    mSockets.remove(webSocket)
                }
            }
        }
    }


    override fun onCreate() {
        super.onCreate()
        mOrientationListener = object : OrientationEventListener(this, SensorManager.SENSOR_DELAY_NORMAL) {

            override fun onOrientationChanged(orientation: Int) {
                Log.i("Rotatomatic", "o: $orientation")

                for (socket in mSockets)
                    socket.send(orientation.toString())
            }
        }
    }

    override fun onStartCommand(intent: Intent?, flags: Int, startId: Int): Int {
        // Start orientation listener
        if (mOrientationListener.canDetectOrientation()) {
            Toast.makeText(this, "Can DetectOrientation", Toast.LENGTH_SHORT).show()
            mOrientationListener.enable()
        } else {
            Toast.makeText(this, "Can't DetectOrientation", Toast.LENGTH_SHORT).show()
        }

        // Start WebSocket server
        httpServer.listen(AsyncServer.getDefault(), 12345)

        return super.onStartCommand(intent, flags, startId)
    }

    override fun onDestroy() {
        super.onDestroy()
        mOrientationListener.disable()
    }

    override fun onBind(intent: Intent): IBinder? {
        return null
    }
}
