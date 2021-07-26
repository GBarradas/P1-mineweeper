float generate_board(float board[50][50],int nlinha, int ncoluna, int mines);
float print_board(float board[50][50],float show_board[50][50], int nlinha, int ncoluna);
int game_over(float board[50][50], float show_board[50][50],int nlinha, int ncoluna, int line, int colun);
float win(float board[50][50],float show_board[50][50],int nlinha,int ncoluna);
int uncover(float board[50][50], float show_board[50][50],int nlinha, int ncoluna, int line, int coluna);
int flag(float board[50][50], float show_board[50][50], int lin, int col);  
