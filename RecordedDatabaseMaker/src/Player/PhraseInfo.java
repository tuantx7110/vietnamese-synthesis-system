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

    /**
     * @return the phraseContent
     */
    public String getPhraseContent() {
        return phraseContent;
    }

    /**
     * @param phraseContent the phraseContent to set
     */
    public void setPhraseContent(String phraseContent) {
        this.phraseContent = phraseContent;
    }

    /**
     * @return the audioFilename
     */
    public String getAudioFilename() {
        return audioFilename;
    }

    /**
     * @param audioFilename the audioFilename to set
     */
    public void setAudioFilename(String audioFilename) {
        this.audioFilename = audioFilename;
    }

    /**
     * @return the startFrame
     */
    public int getStartFrame() {
        return startFrame;
    }

    /**
     * @param startFrame the startFrame to set
     */
    public void setStartFrame(int startFrame) {
        this.startFrame = startFrame;
    }

    /**
     * @return the finishFrame
     */
    public int getFinishFrame() {
        return finishFrame;
    }

    /**
     * @param finishFrame the finishFrame to set
     */
    public void setFinishFrame(int finishFrame) {
        this.finishFrame = finishFrame;
    }
}
