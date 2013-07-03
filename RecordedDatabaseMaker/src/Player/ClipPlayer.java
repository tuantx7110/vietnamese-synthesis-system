package Player;

import java.io.File;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.swing.JButton;

public class ClipPlayer {

    private Clip clip;

    public ClipPlayer(File audioFile) throws Exception {
        clip = AudioSystem.getClip();
        AudioInputStream audio_input_stream = AudioSystem.getAudioInputStream(audioFile);
        clip.open(audio_input_stream);
    }

    public void play(int start, int finish) {
        if (start >= finish || finish >= clip.getFrameLength()) {
            return;
        }

        clip.setFramePosition(start);
        clip.setLoopPoints(start, finish);

        clip.start();

        while (clip.isRunning() && clip.getFramePosition() <= finish) {
            try {
                Thread.sleep(1);
            } catch (InterruptedException ex) {
                Logger.getLogger(ClipPlayer.class.getName()).log(Level.SEVERE, null, ex);
            }
        }

        clip.stop();
    }
}
