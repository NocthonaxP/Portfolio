import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferedImage;
import javax.sound.sampled.Clip;
import javax.swing.JPanel;
import javax.swing.Timer;

public class World_board extends JPanel implements KeyListener, MouseListener, MouseMotionListener {

	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private Clip music; 
	
	private BufferedImage background, pause, refresh;
	private BufferedImage block;
	private final int block_size = 30;
	private final int board_width = 10, board_height = 20;

	private int[][] board = new int[board_height][board_width];

	private Shape_gen[] shapes = new Shape_gen[7];

	private Shape_gen current_shape, next_shape;

	private Timer loop_timer;

	private final int fps = 59;

	private final int delay = 1000 / fps;
	
	private int mouse_x, mouse_y;
	
	private boolean left_click = false;
	
	private Rectangle stop_bounds, refresh_bounds;
	
	private boolean game_paused = false;
	
	private boolean game_over = false;

private Timer buttonLapse = new Timer (300, new ActionListener() {
		
		public void actionPerformed(ActionEvent e) {
			buttonLapse.stop();
			
		}});


private int score = 0; 
	
	
	
	
	public World_board() {

		
		block = Image_loader.loadImage("/tetris_base_tiles.png");
	background = Image_loader.loadImage("/background.png");
		pause = Image_loader.loadImage("/Pause.png");
		refresh = Image_loader.loadImage("/refresh.png");
	music = Image_loader.LoadSound("/music.wav");
		
		
		music.loop(Clip.LOOP_CONTINUOUSLY);
		
		mouse_y=0;
		mouse_x=0;
		
		
		stop_bounds = new Rectangle(350, 500, pause.getWidth(), pause.getHeight() + pause.getHeight()/2);
		refresh_bounds = new Rectangle(350, 500 - refresh.getHeight() - 20,refresh.getWidth(),
				refresh.getHeight() + refresh.getHeight()/2);
		
		loop_timer = new Timer(delay, new Game_looper());

		// shape_gen

		shapes[0] = new Shape_gen(new int[][] { { 1, 1, 1, 1 } // I shape;
		}, block.getSubimage(0, 0, block_size, block_size), this,1);

		shapes[1] = new Shape_gen(new int[][] { { 1, 1, 1 }, { 0, 1, 0 }, // T shape;
		}, block.getSubimage(block_size, 0, block_size, block_size), this,2);

		shapes[2] = new Shape_gen(new int[][] { { 1, 1, 1 }, { 1, 0, 0 }, // L shape;
		}, block.getSubimage(block_size * 2, 0, block_size, block_size), this,3);

		shapes[3] = new Shape_gen(new int[][] { { 1, 1, 1 }, { 0, 0, 1 }, // J shape;
		}, block.getSubimage(block_size * 3, 0, block_size, block_size), this,4);

		shapes[4] = new Shape_gen(new int[][] { { 0, 1, 1 }, { 1, 1, 0 }, // S shape;
		}, block.getSubimage(block_size * 4, 0, block_size, block_size), this,5);

		shapes[5] = new Shape_gen(new int[][] { { 1, 1, 0 }, { 0, 1, 1 }, // Z shape;
		}, block.getSubimage(block_size * 5, 0, block_size, block_size), this,6);

		shapes[6] = new Shape_gen(new int[][] { { 1, 1 }, { 1, 1 }, // O shape;
		}, block.getSubimage(block_size * 6, 0, block_size, block_size), this,7);


	}

	public void paintComponent(Graphics graphics) {
		
		
super.paintComponent(graphics);
		
		graphics.drawImage(background, 0, 0, null);
		
		
		for(int row = 0; row < board.length; row++)
		{
			for(int col = 0; col < board[row].length; col ++)
			{
				
				if(board[row][col] != 0)
				{
					
					graphics.drawImage(block.getSubimage((board[row][col] - 1)*block_size,
							0, block_size, block_size), col*block_size, row*block_size, null);
				}				
					
			}
		}
		for(int row = 0; row < next_shape.get_coordinates().length; row ++)
		{
			for(int col = 0; col < next_shape.get_coordinates()[0].length; col ++)
			{
				if(next_shape.get_coordinates()[row][col] != 0)
				{
					graphics.drawImage(next_shape.get_block(), col*30 + 320, row*30 + 50, null);	
				}
			}		
		}
		current_shape.render(graphics);
		
		if(stop_bounds.contains(mouse_x, mouse_y))
			graphics.drawImage(pause.getScaledInstance(pause.getWidth() + 3, pause.getHeight() + 3, BufferedImage.SCALE_DEFAULT)
					, stop_bounds.x + 3, stop_bounds.y + 3, null);
		else
			graphics.drawImage(pause, stop_bounds.x, stop_bounds.y, null);
		
		if(refresh_bounds.contains(mouse_x, mouse_y))
			graphics.drawImage(refresh.getScaledInstance(refresh.getWidth() + 3, refresh.getHeight() + 3,
					BufferedImage.SCALE_DEFAULT), refresh_bounds.x + 3, refresh_bounds.y + 3, null);
		else
			graphics.drawImage(refresh, refresh_bounds.x, refresh_bounds.y, null);
		
		
		if(game_paused)
		{
			String gamePausedString = "GAME PAUSED";
			graphics.setColor(Color.WHITE);
			graphics.setFont(new Font("Georgia", Font.BOLD, 30));
			graphics.drawString(gamePausedString, 35, Game_Window.HEIGHT/2);
		}
		if(game_over)
		{
			String gameOverString = "GAME OVER";
			graphics.setColor(Color.WHITE);
			graphics.setFont(new Font("Georgia", Font.BOLD, 30));
			graphics.drawString(gameOverString, 50, Game_Window.HEIGHT/2);
		}	
		graphics.setColor(Color.WHITE);
		
		graphics.setFont(new Font("Georgia", Font.BOLD, 20));
		
		graphics.drawString("SCORE", Game_Window.WIDTH - 125,Game_Window.HEIGHT/2);
		graphics.drawString(score+"", Game_Window.WIDTH - 125, Game_Window.HEIGHT/2 + 30);
		
		Graphics2D g2d = (Graphics2D)graphics;
		
		g2d.setStroke(new BasicStroke(2));
		g2d.setColor(new Color(0, 0, 0, 100));
		
		for(int i = 0; i <= board_height; i++)
		{
			g2d.drawLine(0, i*block_size, board_width*block_size, i*block_size);
		}
		for(int j = 0; j <= board_width; j++)
		{
			g2d.drawLine(j*block_size, 0, j*block_size, board_height*30);
		}
	
	
	
	}

	public void update() {
		
		if(stop_bounds.contains(mouse_x, mouse_y) && left_click && !buttonLapse.isRunning() && !game_over)
		{
			buttonLapse.start();
			game_paused = !game_paused;
		}
		
		if(refresh_bounds.contains(mouse_x, mouse_y) && left_click)
			start_game();
		
		if(game_paused || game_over)
		{
			return;
		}
		
		current_shape.Update();
	}
	
	
	
	public void setcurrent_shape(){
		current_shape = next_shape;
		set_new_shape();
		
		for(int row = 0; row < current_shape.get_coordinates().length; row ++)
		{
			for(int col = 0; col < current_shape.get_coordinates()[0].length; col ++)
			{
				if(current_shape.get_coordinates()[row][col] != 0)
				{
					if(board[current_shape.get_y() + row][current_shape.get_x() + col] != 0)
						game_over = true;
				}
			}		
		}
		
	}
	

	public int get_block_size() {
		return block_size;
	}

	@Override
	public void keyTyped(KeyEvent e) {
		// dont need but needs to be implemented

	}

	@Override
	public void keyPressed(KeyEvent e) {
		if (e.getKeyCode() == KeyEvent.VK_LEFT) {
			current_shape.set_offset_x(-1);
		}
		if (e.getKeyCode() == KeyEvent.VK_RIGHT) {
			current_shape.set_offset_x(1);
		}
		if (e.getKeyCode() == KeyEvent.VK_DOWN) {
			current_shape.down_speed();
		}
		if (e.getKeyCode() == KeyEvent.VK_UP) {
			current_shape.rotate();
		}

	}

	@Override
	public void keyReleased(KeyEvent e) {
		if (e.getKeyCode() == KeyEvent.VK_DOWN) {
			current_shape.base_speed();
		}

	}

	public void set_new_shape() {
		int index = (int)(Math.random()*shapes.length);
		next_shape = new Shape_gen(shapes[index].get_coordinates(), shapes[index].get_block(), this, shapes[index].get_colour());
	}

	public void start_game(){
		stop_game();
		set_new_shape();
		setcurrent_shape();
		game_over = false;
		loop_timer.start();
		
	}
	
	public void stop_game(){
		score = 0;
		
		for(int row = 0; row < board.length; row++)
		{
			for(int col = 0; col < board[row].length; col ++)
			{
				board[row][col] = 0;
			}
		}
		loop_timer.stop();
	}
	
	class Game_looper implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent e) {
			update();
			repaint();
		}
		
	}


	@Override
	public void mouseDragged(MouseEvent e) {
		mouse_x = e.getX();
		mouse_y = e.getY();
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		mouse_x = e.getX();
		mouse_y = e.getY();
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		
	}

	@Override
	public void mousePressed(MouseEvent e) {
		if(e.getButton() == MouseEvent.BUTTON1)
			left_click = true;
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		if(e.getButton() == MouseEvent.BUTTON1)
			left_click = false;
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		
	}
	
	public void addScore(){
		score ++;
	}
	
	public int[][] get_board(){
		return board;
	}
		
	

}
