import java.awt.Color;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JPanel;
import javax.swing.Timer;

public class Title extends JPanel implements MouseListener, MouseMotionListener{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int mouseX, mouseY;
	private Rectangle bounds;
	private boolean leftClick = false;
	private BufferedImage title, instructions, play;
	private Game_Window window;
	private BufferedImage[] playButton = new BufferedImage[2];
	private Timer timer;
	
	
	public Title(Game_Window window){
		try {
			title = ImageIO.read(World_board.class.getResource("/Title.png"));
			instructions = ImageIO.read(World_board.class.getResource("/arrow.png"));
			play = ImageIO.read(World_board.class.getResource("/play.png"));
		} catch (IOException e) {
			e.printStackTrace();
		}
		timer = new Timer(1000/60, new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent e) {
				repaint();
			}
			
		});
		timer.start();
		mouseX = 0;
		mouseY = 0;
		
		playButton[0] = play.getSubimage(0, 0, 100, 80);
		playButton[1] = play.getSubimage(100, 0, 100, 80);
		
		bounds = new Rectangle(Game_Window.WIDTH/2 - 50, Game_Window.HEIGHT/2 - 100, 100, 80);
		this.window = window;
		
		
		
	}
	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		
		if(leftClick && bounds.contains(mouseX, mouseY))
			window.startTetris();
			
		g.setColor(Color.BLACK);
		
		g.fillRect(0, 0, Game_Window.WIDTH, Game_Window.HEIGHT);
		
		g.drawImage(title, Game_Window.WIDTH/2 - title.getWidth()/2, Game_Window.HEIGHT/2 - title.getHeight()/2 - 200, null);
		g.drawImage(instructions, Game_Window.WIDTH/2 - instructions.getWidth()/2,
				Game_Window.HEIGHT/2 - instructions.getHeight()/2 + 150, null);
		
		if(bounds.contains(mouseX, mouseY))
			g.drawImage(playButton[0], Game_Window.WIDTH/2 - 50, Game_Window.HEIGHT/2 - 100, null);
		else
			g.drawImage(playButton[1], Game_Window.WIDTH/2 - 50, Game_Window.HEIGHT/2 - 100, null);
		
		
	}

	@Override
	public void mouseClicked(MouseEvent e) {	
	}

	@Override
	public void mousePressed(MouseEvent e) {
		if(e.getButton() == MouseEvent.BUTTON1)
			leftClick = true;
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		if(e.getButton() == MouseEvent.BUTTON1)
			leftClick = false;
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
	}

	@Override
	public void mouseDragged(MouseEvent e) {
		mouseX = e.getX();
		mouseY = e.getY();
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		mouseX = e.getX();
		mouseY = e.getY();
	}	
}