import javax.swing.JFrame;

public class Game_Window {

	
public static final int WIDTH = 445, HEIGHT = 629;
	
	private World_board board;
	private Title title;
	private JFrame window;
	
	public Game_Window(){
		
		window = new JFrame("Tetris");
		window.setSize(WIDTH, HEIGHT);
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		window.setLocationRelativeTo(null);
		window.setResizable(false);	
		
		board = new World_board();
		title = new Title(this);
		
		window.addKeyListener(board);
		window.addMouseMotionListener(title);
		window.addMouseListener(title);
		
		window.add(title);
		
		window.setVisible(true);
	}
	public void startTetris(){
		window.remove(title);
		window.addMouseMotionListener(board);
		window.addMouseListener(board);
		window.add(board);
		board.start_game();
		window.revalidate();
	}
	
	public static void main(String[] args) {
		new Game_Window();
	}

	
}
