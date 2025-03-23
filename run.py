import subprocess
import itertools
import sys

def run_program(prog_path, input_data):
    """
    執行指定的程式，將 input_data 傳入標準輸入，並回傳標準輸出（字串）
    """
    try:
        proc = subprocess.Popen(prog_path, 
                                stdin=subprocess.PIPE, 
                                stdout=subprocess.PIPE, 
                                stderr=subprocess.PIPE, 
                                text=True)
        stdout, stderr = proc.communicate(input=input_data)
    except Exception as e:
        print(f"Error running {prog_path}: {e}")
        sys.exit(1)
        
    if proc.returncode != 0:
        print(f"程式 {prog_path} 執行失敗，返回碼: {proc.returncode}\n錯誤訊息: {stderr}")
        sys.exit(1)
    return stdout.strip()

def generate_test_cases():
    """
    使用 itertools.combinations 產生測資範例
    例如：從 1~9 中選取三個數字（可根據實際需求修改）
    """
    for comb in itertools.combinations(range(1, 10), 3):
        # 這裡將組合轉成以空白分隔的字串，並以換行結尾
        yield " ".join(map(str, comb)) + "\n"

def differential_test(prog1, prog2, max_tests=1000):
    """
    產生測資並同時將測資傳入兩個程式，對比其輸出是否相同
    """
    test_count = 0
    for test_input in generate_test_cases():
        test_count += 1
        
        output1 = run_program(prog1, test_input)
        output2 = run_program(prog2, test_input)
        
        if output1 != output2:
            print("測試資料發現不一致！")
            print("測資：", test_input.strip())
            print(f"{prog1} 輸出：", output1)
            print(f"{prog2} 輸出：", output2)
            sys.exit(1)
        
        # 若測試次數達到預設值則結束
        if test_count >= max_tests:
            break

    print(f"所有 {test_count} 個測試均通過。")

if __name__ == "__main__":
    # 修改以下路徑為你的 C++ 可執行檔路徑
    prog1_path = "./prog1"  
    prog2_path = "./prog2"
    
    differential_test(prog1_path, prog2_path)
