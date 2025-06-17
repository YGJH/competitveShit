import subprocess
import time
import sys
import signal

"""
Simple watcher script: runs `uv run main.py`, and upon exit, automatically restarts.
Use Ctrl+C to stop the watcher.
"""

def run_and_watch():
    cmd = ["uv", "run", "main.py"]
    try:
        while True:
            print(f"Starting: {' '.join(cmd)}")
            process = subprocess.Popen(cmd)
            exit_code = process.wait()
            print(f"Process exited with code {exit_code}. Restarting in 1s...")
            time.sleep(1)
    except KeyboardInterrupt:
        print("Watcher interrupted. Exiting.")
        sys.exit(0)

if __name__ == '__main__':
    run_and_watch()
