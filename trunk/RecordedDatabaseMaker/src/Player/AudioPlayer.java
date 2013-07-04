package Player;

import java.io.File;
import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.DataLine;
import javax.sound.sampled.SourceDataLine;

public class AudioPlayer {

    public static final int BUFFER_SIZE = 64 * 1024;
    private File audioFile;
    private AudioFormat audioFormat;
    private AudioInputStream audioInputStream;
    private SourceDataLine soundLine;

    public AudioPlayer(File audioFile) throws Exception {
        this.audioFile = audioFile;
    }

    public void play(int startFrame, int finishFrame) {
        try {
            audioInputStream = AudioSystem.getAudioInputStream(audioFile);
            audioFormat = audioInputStream.getFormat();
            DataLine.Info info = new DataLine.Info(SourceDataLine.class, audioFormat);
            soundLine = (SourceDataLine) AudioSystem.getLine(info);
            soundLine.open(audioFormat);
            soundLine.start();

            long skipLength = (long) startFrame * audioFormat.getFrameSize();
            audioInputStream.skip(skipLength);

            long playLength = (long) (finishFrame - startFrame + 1) * audioFormat.getFrameSize();
            byte[] data = new byte[BUFFER_SIZE];

            while (playLength > 0) {
                int readLength = audioInputStream.read(data, 0, (int) Math.min(playLength, data.length));
                if (readLength <= 0) {
                    break;
                }
                soundLine.write(data, 0, readLength);
                playLength -= readLength;
            }

            soundLine.drain();
            soundLine.close();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}
