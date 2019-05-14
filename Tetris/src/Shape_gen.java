import java.awt.Graphics;
import java.awt.image.BufferedImage;

public class Shape_gen {
	
	private BufferedImage block; 
	
	private int[][] coordinates; 
	private int [][] reference;
	private World_board board;
	private int x_offset=0;
	private int x,y;
	private int colour;
	

	
	private boolean collided= false, move_x=false;
	
	
	private int base_speed = 600, down_speed = 30 , current_speed, delay;
	
	private long time, last_time;

	
	
	public Shape_gen(int[][] coord, BufferedImage block, World_board board, int colour) {
		this.block = block;
		this.coordinates = coord;
		this.board = board;
		this.colour=colour;
		
		x_offset=0;
		current_speed= base_speed;
		time=0;
		delay=base_speed;
		x=4;
		y=0;
		
		
		last_time=System.currentTimeMillis();
		reference = new int[coordinates.length][coordinates[0].length];
	
		
		System.arraycopy(coordinates, 0, reference, 0, coordinates.length);
	}


	public void Update() {
		
		move_x = true;
		time += System.currentTimeMillis() - last_time;
		last_time = System.currentTimeMillis();
		
		if(collided)
		{
			for(int row = 0; row < coordinates.length; row ++)
			{
				for(int col = 0; col < coordinates[0].length; col ++)
				{
					if(coordinates[row][col] != 0)
						board.get_board()[y + row][x + col] = colour;
				}
			}
			checkLine();
			board.addScore();
			board.setcurrent_shape();
		}
		
		if(!(x + x_offset + coordinates[0].length > 10) && !(x + x_offset < 0))
		{
			
			for(int row = 0; row < coordinates.length; row++)
			{
				for(int col = 0; col < coordinates[row].length; col ++)
				{
					if(coordinates[row][col] != 0)
					{
						if(board.get_board()[y + row][x + x_offset + col] != 0)
						{
							move_x = false;
						}
						
					}
				}
			}
			
			if(move_x)
				x += x_offset;
			
		}
		
		if(!(y + 1 + coordinates.length > 20))
		{
			
			for(int row = 0; row < coordinates.length; row++)
			{
				for(int col = 0; col < coordinates[row].length; col ++)
				{
					if(coordinates[row][col] != 0)
					{
						
						if(board.get_board()[y+1 + row][x +  col] != 0)
						{
							collided = true;
						}
					}
				}
			}
			if(time > delay)
				{
					y++;
					time = 0;
				}
		}else{
			collided = true;
		}
		
		x_offset = 0;
		
	}
	
	public void render(Graphics graph) {
		
		for(int row = 0; row < coordinates.length; row ++)
		{
			for(int col = 0; col < coordinates[0].length; col ++)
			{
				if(coordinates[row][col] != 0)
				{
					graph.drawImage(block, col*30 + x*30, row*30 + y*30, null);	
				}
			}		
		}
		
		for(int row = 0; row < reference.length; row ++)
		{
			for(int col = 0; col < reference[0].length; col ++)
			{
				if(reference[row][col] != 0)
				{
					graph.drawImage(block, col*30 + 320, row*30 + 160, null);	
				}	
				
			}
				
		}

	}
	
	private void checkLine(){
		int size = board.get_board().length - 1;
		
		for(int i = board.get_board().length - 1; i > 0; i--)
		{
			int count = 0;
			for(int j = 0; j < board.get_board()[0].length; j++)
			{
				if(board.get_board()[i][j] != 0)
					count++;
				
				board.get_board()[size][j] = board.get_board()[i][j];
			}
			if(count < board.get_board()[0].length)
				size --;
		}
	}
	
public void rotate() {
		int [][] rotated_matrix = null;
			
			rotated_matrix = get_transposed_matrix(coordinates);
		
		rotated_matrix= get_reversed_matrix(rotated_matrix);
		
		if(x + rotated_matrix[0].length > 10 || y + rotated_matrix.length > 20 ) {
			return;
		}
		
		
		
			for(int row = 0; row < rotated_matrix.length; row++)
			{
				for(int col = 0; col < rotated_matrix[row].length; col ++)
				{
					if(rotated_matrix[row][col] != 0)
					{
						if(board.get_board()[y + row][x + col] != 0)
						{
							return;
						}
					}
				}
			}
		coordinates= rotated_matrix;
	}
	
	private int [][] get_transposed_matrix ( int[][] matrix){
		
		int [][] trans_Matrix = new int[matrix[0].length][matrix.length];
		
		for(int i=0; i<matrix.length;++i) {
			for(int j=0; j<matrix[0].length;++j) {
				trans_Matrix[j][i] = matrix[i][j];
			}
		}
		
		return trans_Matrix;
		
	}
	
	
	private int [][] get_reversed_matrix ( int[][] matrix){
		
		int middle= matrix.length/2;
		
		for(int i=0; i<middle; ++i) {
			int[]mat= matrix[i];
			matrix[i]= matrix[matrix.length -1 -i];
			matrix[matrix.length -1 -i]=mat;
		}
		return matrix;
		
	}


	public BufferedImage get_block() {
		return block;
	}


	public int[][] get_coordinates() {
		return coordinates;
	}


	public int get_colour() {
		return colour;
	}
	
	public int get_x(){
		return x;
	}
	
	public int get_y(){
		return y;
	}
	
	public void set_offset_x(int x_off){
		this.x_offset = x_off;
	}
	
	public void down_speed(){
		delay = down_speed;
	}
	
	public void base_speed(){
		delay = base_speed;
	}
	
}
