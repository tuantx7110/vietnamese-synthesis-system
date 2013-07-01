package Player;

public class PhraseInfo {

    private String phraseContent;
    private String audioFilename;
    private int startFrame;
    private int finishFrame;

    public PhraseInfo(String phraseContent, String audioFilename, int startFrame, int finishFrame) {
        this.phraseContent = phraseContent;
        this.audioFilename = audioFilename;
        this.startFrame = startFrame;
        this.finishFrame = finishFrame;
    }
}
