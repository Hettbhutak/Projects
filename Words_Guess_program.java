import javax.swing.;
import java.awt.;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

class WordGuessingGame extends JFrame {
private JLabel guessLabel;
private JTextField guessField;
private JButton guessButton;
private JLabel resultLabel;
private int attemptsLeft;
private String secretWord;

public WordGuessingGame() {
    setTitle("Word Guessing Game");
    setSize(300, 200);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    setLayout(new FlowLayout());
	
    guessLabel = new JLabel("Guess fruit name:");
    guessField = new JTextField(15);
    guessButton = new JButton("Guess");
    resultLabel = new JLabel();

    add(guessLabel);
    add(guessField);
    add(guessButton);
    add(resultLabel);

    guessButton.addActionListener(new ActionListener() {
        @Override
        public void actionPerformed(ActionEvent e) {
            checkGuess();
        }
    });

    initializeGame();
}

private void initializeGame() {
    String[] words = {"apple", "banana", "orange", "grape", "watermelon"};
    Random rand = new Random();
    secretWord = words[rand.nextInt(words.length)];
    attemptsLeft = 3;
    resultLabel.setText("Attempts left: " + attemptsLeft);
}

private void checkGuess() {
    String guess = guessField.getText().toLowerCase();
    if (guess.equals(secretWord)) {
        resultLabel.setText("Congratulations! You guessed the word.");
        guessField.setEditable(false);
        guessButton.setEnabled(false);
    } else {
        attemptsLeft--;
        if (attemptsLeft == 0) {
            resultLabel.setText("Sorry, you're out of attempts. The word was: " + secretWord);
            guessField.setEditable(false);
            guessButton.setEnabled(false);
        } else {
            resultLabel.setText("Incorrect guess. Attempts left: " + attemptsLeft);
        }
    }
    guessField.setText("");
}

public static void main(String[] args) {
    SwingUtilities.invokeLater(new Runnable() {
        @Override
        public void run() {
            new WordGuessingGame().setVisible(true);
        }
    });
}
}
