#include <iostream>
#include <vector>
#include <string>
#include <fstream>    // 用於檔案 I/O (與 AI 程式溝通)
#include <cstdlib>    // 用於 system()
#include <cstdio>     // 用於 remove()
#include <algorithm>  // 用於 std::find
#include <stdexcept>  // 用於 std::runtime_error

// --- 全域常數 ---
const int BOARD_SIZE = 6;
const char EMPTY = '+';
const char PLAYER_X = 'X'; // AI 1 (ac.cpp)
const char PLAYER_O = 'O'; // AI 2 (wa.cpp)
const int AI1_DEPTH = 7;   // ac 搜索深度 (你可以調整)
const int AI2_DEPTH = 9;   // wa 搜索深度 (你可以調整)

// --- 類型定義 ---
using OthelloBoard = std::vector<std::vector<char>>;

// --- 輔助函式：字元座標轉整數 ---
int charToCoord(char c) {
    if (c >= 'A' && c <= 'F') return c - 'A'; // Row
    if (c >= 'a' && c <= 'f') return c - 'a'; // Col
    return -1; // 無效字元
}

// --- 輔助函式：整數座標轉字元 (用於顯示) ---
char coordToCharRow(int r) { return 'A' + r; }
char coordToCharCol(int c) { return 'a' + c; }
// --- 函式宣告 ---
void initializeBoard(OthelloBoard& board);
void printBoard(const OthelloBoard& board);
std::string boardToString(const OthelloBoard& board);
std::pair<int, int> parseAIMove(const std::string& moveStr);
bool isMoveValidOnBoard(const OthelloBoard& board, int r, int c, char player);
std::vector<std::pair<int, int>> getValidMoves(const OthelloBoard& board, char player);
void applyMove(OthelloBoard& board, int r, int c, char player);
std::string runAI(const std::string& ai_executable, const OthelloBoard& currentBoard, char player_char, int AI1_DEPTH , int AI2_DEPTH);
void countScores(const OthelloBoard& board, int& scoreX, int& scoreO);

// --- 主遊戲邏輯 ---
int main() {
    OthelloBoard board(BOARD_SIZE, std::vector<char>(BOARD_SIZE));
    initializeBoard(board);

    // char currentPlayer = PLAYER_X; // X (ac.cpp) 先手
    char currentPlayer = PLAYER_X; // O (wa.cpp) 先手
    std::string ai1_executable = "ac"; // 在 Windows 上
    std::string ai2_executable = "wa"; // 在 Windows 上
    // 在 Linux/macOS 上可能是 "./ac" 和 "./wa"

    int consecutive_passes = 0;
    int turn_count = 0;
    const int MAX_TURNS = BOARD_SIZE * BOARD_SIZE - 4; // 初始有4子

    std::cout << "Othello Game Runner Started!" << std::endl;
    std::cout << "Player X (AI1 - " << ai1_executable << ") vs Player O (AI2 - " << ai2_executable << ")" << std::endl;
    std::cout << "AI Search Depth: " << AI1_DEPTH << ' ' << AI2_DEPTH << std::endl;


    while (turn_count < MAX_TURNS) {
        std::cout << "\n--- Turn " << turn_count + 1 << ", Player " << currentPlayer << " (" << ((currentPlayer == PLAYER_X) ? ai1_executable : ai2_executable) << ") ---" << std::endl;
        printBoard(board);

        std::vector<std::pair<int, int>> validMoves = getValidMoves(board, currentPlayer);

        if (validMoves.empty()) {
            std::cout << "Player " << currentPlayer << " has no valid moves. Pass." << std::endl;
            consecutive_passes++;
            if (consecutive_passes >= 2) {
                std::cout << "Both players passed consecutively. Game over." << std::endl;
                break;
            }
            currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
            // turn_count++; // Pass也算一個回合的結束，但不增加實際下子數
            continue;
        } else {
            consecutive_passes = 0; // 重置連續 pass 計數器
        }

        std::string current_ai_exe = (currentPlayer == PLAYER_X) ? ai1_executable : ai2_executable;
        std::string ai_move_str = runAI(current_ai_exe, board, currentPlayer, AI1_DEPTH , AI2_DEPTH);

        if (ai_move_str == "pass" || ai_move_str.empty()) {
            std::cout << "AI for player " << currentPlayer << " (" << current_ai_exe << ") chose to pass or failed to provide a move." << std::endl;
            // 視為 AI pass
            consecutive_passes++;
            if (consecutive_passes >= 2) {
                std::cout << "Both players passed consecutively (one due to AI pass/fail). Game over." << std::endl;
                break;
            }
            currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
            // turn_count++;
            continue;
        }

        std::pair<int, int> move = parseAIMove(ai_move_str);

        bool chosen_move_is_valid = false;
        for(const auto& valid_m : validMoves){
            if(valid_m.first == move.first && valid_m.second == move.second){
                chosen_move_is_valid = true;
                break;
            }
        }

        if (move.first == -1 || !chosen_move_is_valid) {
            std::cout << "Player " << currentPlayer << " (" << current_ai_exe << ") made an invalid move: " << ai_move_str
                      << " (parsed as " << move.first << "," << move.second << ")." << std::endl;
            std::cout << "Valid moves were: ";
            for(const auto& vm : validMoves) std::cout << "[" << coordToCharRow(vm.first) << coordToCharCol(vm.second) << "] ";
            std::cout << std::endl;
            std::cout << "Opponent wins by default due to invalid move." << std::endl;
            if (currentPlayer == PLAYER_X) std::cout << "Player O (AI2 - " << ai2_executable << ") wins!" << std::endl;
            else std::cout << "Player X (AI1 - " << ai1_executable << ") wins!" << std::endl;
            break;
        }

        std::cout << "Player " << currentPlayer << " chooses: " << coordToCharRow(move.first) << coordToCharCol(move.second) << std::endl;
        applyMove(board, move.first, move.second, currentPlayer);
        turn_count++; // 實際下子才增加

        // 檢查遊戲是否因雙方都無棋可下而結束
        if (getValidMoves(board, PLAYER_X).empty() && getValidMoves(board, PLAYER_O).empty()){
            std::cout << "No more valid moves for either player. Game Over." << std::endl;
            printBoard(board); // 顯示最終棋盤
            break;
        }

        currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
    }

    std::cout << "\n========== GAME OVER ==========" << std::endl;
    std::cout << "Final Board:" << std::endl;
    printBoard(board);

    int scoreX, scoreO;
    countScores(board, scoreX, scoreO);
    std::cout << "\nFinal Scores:" << std::endl;
    std::cout << "Player X (AI1 - " << ai1_executable << "): " << scoreX << std::endl;
    std::cout << "Player O (AI2 - " << ai2_executable << "): " << scoreO << std::endl;

    if (scoreX > scoreO) std::cout << "Player X (AI1 - " << ai1_executable << ") WINS!" << std::endl;
    else if (scoreO > scoreX) std::cout << "Player O (AI2 - " << ai2_executable << ") WINS!" << std::endl;
    else std::cout << "It's a DRAW!" << std::endl;

    // 清理臨時檔案
    remove("temp_ai_input.txt");
    remove("temp_ai_output.txt");

    return 0;
}

// --- 函式實作 ---

void initializeBoard(OthelloBoard& board) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = EMPTY;
        }
    }
    // Othello 6x6 初始佈局 (通常是中央)
    // 假設棋盤中央是 (2,2), (2,3), (3,2), (3,3)
    // 如果你的 AI 期望不同的初始狀態，請調整
    board[BOARD_SIZE/2 - 1][BOARD_SIZE/2 - 1] = PLAYER_O; // 例如 'O'
    board[BOARD_SIZE/2 - 1][BOARD_SIZE/2    ] = PLAYER_X; // 例如 'X'
    board[BOARD_SIZE/2    ][BOARD_SIZE/2 - 1] = PLAYER_X; // 例如 'X'
    board[BOARD_SIZE/2    ][BOARD_SIZE/2    ] = PLAYER_O; // 例如 'O'
}

void printBoard(const OthelloBoard& board) {
    std::cout << "  ";
    for (int j = 0; j < BOARD_SIZE; ++j) std::cout << coordToCharCol(j) << " ";
    std::cout << std::endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << coordToCharRow(i) << " ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::string boardToString(const OthelloBoard& board) {
    std::string s = "";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            s += board[i][j];
        }
    }
    return s;
}

std::pair<int, int> parseAIMove(const std::string& moveStr) {
    // 預期格式: "[RC]" e.g., "[Ca]"
    if (moveStr.length() == 4 && moveStr[0] == '[' && moveStr[3] == ']') {
        int r = charToCoord(moveStr[1]); // Row char e.g., 'C'
        int c = charToCoord(moveStr[2]); // Col char e.g., 'a'
        if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE) {
            return {r, c};
        }
    }
    return {-1, -1}; // 無效格式或內容
}

// 檢查在 (r, c) 下子是否為 player 的合法走位
bool isMoveValidOnBoard(const OthelloBoard& board, int r, int c, char player) {
    if (r < 0 || r >= BOARD_SIZE || c < 0 || c >= BOARD_SIZE || board[r][c] != EMPTY) {
        return false;
    }

    char opponent = (player == PLAYER_X) ? PLAYER_O : PLAYER_X;
    bool move_is_possible = false;

    // 8 個方向
    int dr[] = {-1, -1, -1,  0, 0,  1, 1, 1};
    int dc[] = {-1,  0,  1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; ++i) {
        int cur_r = r + dr[i];
        int cur_c = c + dc[i];
        bool opponent_pieces_found_in_line = false;

        while (cur_r >= 0 && cur_r < BOARD_SIZE && cur_c >= 0 && cur_c < BOARD_SIZE && board[cur_r][cur_c] == opponent) {
            opponent_pieces_found_in_line = true;
            cur_r += dr[i];
            cur_c += dc[i];
        }

        if (opponent_pieces_found_in_line &&
            cur_r >= 0 && cur_r < BOARD_SIZE && cur_c >= 0 && cur_c < BOARD_SIZE &&
            board[cur_r][cur_c] == player) {
            move_is_possible = true;
            break; // 找到一個方向可以翻子即可
        }
    }
    return move_is_possible;
}

std::vector<std::pair<int, int>> getValidMoves(const OthelloBoard& board, char player) {
    std::vector<std::pair<int, int>> moves;
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            if (isMoveValidOnBoard(board, r, c, player)) {
                moves.push_back({r, c});
            }
        }
    }
    return moves;
}

void applyMove(OthelloBoard& board, int r, int c, char player) {
    // 假設此處呼叫前已經驗證過是合法走位
    board[r][c] = player;
    char opponent = (player == PLAYER_X) ? PLAYER_O : PLAYER_X;

    int dr[] = {-1, -1, -1,  0, 0,  1, 1, 1};
    int dc[] = {-1,  0,  1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; ++i) {
        int cur_r = r + dr[i];
        int cur_c = c + dc[i];
        std::vector<std::pair<int, int>> pieces_to_flip;
        bool opponent_pieces_found_in_line = false;

        while (cur_r >= 0 && cur_r < BOARD_SIZE && cur_c >= 0 && cur_c < BOARD_SIZE && board[cur_r][cur_c] == opponent) {
            opponent_pieces_found_in_line = true;
            pieces_to_flip.push_back({cur_r, cur_c});
            cur_r += dr[i];
            cur_c += dc[i];
        }

        if (opponent_pieces_found_in_line &&
            cur_r >= 0 && cur_r < BOARD_SIZE && cur_c >= 0 && cur_c < BOARD_SIZE &&
            board[cur_r][cur_c] == player) {
            // 翻轉這條線上的棋子
            for (const auto& p : pieces_to_flip) {
                board[p.first][p.second] = player;
            }
        }
    }
}

std::string runAI(const std::string& ai_executable, const OthelloBoard& currentBoard, char player_char, int depth_ai1 , int depth_ai2) {
    std::string board_str = boardToString(currentBoard);
    int player_number = (player_char == PLAYER_X) ? 1 : 2; // ac.cpp/wa.cpp 預期 1 for X, 2 for O

    // AI 程式預期輸入格式:
    // t (測試案例數量，這裡固定為1)
    // board_string (36個字元)
    // player_number (1 或 2)
    // depth
    std::string ai_input_content = board_str + "\n" +
                                   std::to_string(player_number) + "\n" +
                                   std::to_string(((player_number==1)?depth_ai1:depth_ai2)) + "\n";

    std::string temp_input_filename = "temp_ai_input.txt";
    std::string temp_output_filename = "temp_ai_output.txt";

    std::ofstream infile(temp_input_filename);
    if (!infile) {
        std::cerr << "Runner Error: Cannot open " << temp_input_filename << " for writing." << std::endl;
        return "pass"; // 表示 AI 執行失敗
    }
    infile << ai_input_content;
    infile.close();

    // 組合命令，例如: ac.exe < temp_ai_input.txt > temp_ai_output.txt
    std::string command = "./" + ai_executable + " < " + temp_input_filename + " > " + temp_output_filename;
    // std::cout << "Runner: Executing command: " << command << std::endl; // 用於偵錯

    int system_ret = system(command.c_str());
    if (system_ret != 0) {
        std::cerr << "Runner Warning: AI program " << ai_executable << " exited with code " << system_ret << "." << std::endl;
        // AI 可能出錯，但還是嘗試讀取其輸出
    }

    std::ifstream outfile(temp_output_filename);
    std::string line;
    std::string ai_move_output = "pass"; // 如果沒讀到有效走位，預設為 pass

    if (!outfile) {
        std::cerr << "Runner Error: Cannot open " << temp_output_filename << " for reading." << std::endl;
        return "pass";
    }

    // AI 程式會先輸出一堆分數，然後才是 "[RC]" 格式的走位
    while (std::getline(outfile, line)) {
        // std::cout << "Runner: AI (" << ai_executable << ") raw output line: " << line << std::endl; // 用於偵錯
        if (line.length() == 4 && line[0] == '[' && line[3] == ']') {
            // 檢查是否為 [大寫字母小寫字母]
            if (isupper(line[1]) && islower(line[2])) {
                 ai_move_output = line;
                 break; // 找到目標走位格式
            }
        }
    }
    outfile.close();

    if (ai_move_output == "pass" && system_ret == 0) {
        // std::cout << "Runner Info: AI " << ai_executable << " might have legitimately passed or output format mismatch." << std::endl;
    }

    return ai_move_output;
}

void countScores(const OthelloBoard& board, int& scoreX, int& scoreO) {
    scoreX = 0;
    scoreO = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == PLAYER_X) scoreX++;
            else if (board[i][j] == PLAYER_O) scoreO++;
        }
    }
}
