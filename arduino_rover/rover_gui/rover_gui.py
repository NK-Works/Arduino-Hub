import tkinter as tk
import time
import serial
from PIL import Image, ImageTk

# Establishing a serial connection with the Arduino
ser = serial.Serial('COM11', 9600) # Change the COM - Port according to your own device

# Defining the initial speed of the car
current_speed = 0

# Creating the GUI window
window = tk.Tk()
window.title("Bluetooth Arduino Car Control")
window.configure(bg="black")

# Getting the screen width and height
screen_width = window.winfo_screenwidth()
screen_height = window.winfo_screenheight()

# Setting the desired width and height for the window
window_width = 800
window_height = 600

# Calculating the x and y positions for centering the window
x = (screen_width // 2) - (window_width // 2)
y = (screen_height // 2) - (window_height // 2)

# Set the window geometry
window.geometry(f"{window_width}x{window_height}+{x}+{y}")

# Loading the background image
background_image = Image.open("./image/background.jpg")
background_photo = ImageTk.PhotoImage(background_image)

# Creating a label for the background image
background_label = tk.Label(window, image=background_photo)
background_label.place(x=0, y=0, relwidth=1, relheight=1)

# Creating a label for the title
lbl_title = tk.Label(window, text="NK-WORKS", font=("Arial", 24, "bold"), fg="white", bg="black")
lbl_title.pack(pady=20)

# Creating a label for the custom message
lbl_message = tk.Label(window, text="Controlling Arduino Rover from PC\n\nMade by Anneshu Nag", font=("Arial", 14, "bold"), fg="black", bg="orange")
lbl_message.pack()

# Defining a function to send commands to the Arduino
def send_command(direction, delay):
    command = direction + ' ' + str(delay)  # Separate direction and speed with a space
    ser.write(command.encode())

# Defining a function to stop the car
def stop_car():
    send_command("stop", 0)
    
# Defining a function to revert the entire car
def revert_car():
    send_command("quit", 0)
    speed_scale.set(0)

# Defining a variable to keep track of the last button press time
last_press_time = 0

def handle_button_press_duration(direction, duration):
    send_command(direction, duration)
    # Updating the last press time for custom duration
    global last_press_time
    last_press_time = time.time()

# Creating a frame to hold the buttons
button_frame = tk.Frame(window, bg="brown")
button_frame.pack(pady=20)

# Creating a frame to hold the buttons
button_frame2 = tk.Frame(window, bg="white")
button_frame2.pack(pady=10)

# Creating the buttons for Forward, Backward, Left, Right, Stop, and Revert commands
btn_forward = tk.Button(button_frame, text="Forward", command=lambda: handle_button_press_duration("forward", 3), width=10, bg="green", fg="white", font=("Arial", 14, "bold"))
btn_backward = tk.Button(button_frame, text="Backward", command=lambda: handle_button_press_duration("backward", 3), width=10, bg="red", fg="white", font=("Arial", 14, "bold"))
btn_left = tk.Button(button_frame, text="Left", command=lambda: handle_button_press_duration("left", 3), width=10, bg="blue", fg="white", font=("Arial", 14, "bold"))
btn_right = tk.Button(button_frame, text="Right", command=lambda: handle_button_press_duration("right", 3), width=10, bg="orange", fg="white", font=("Arial", 14, "bold"))
btn_stop = tk.Button(button_frame, text="Stop", command=lambda: handle_button_press_duration("stop", 3), width=10, bg="gray", fg="white", font=("Arial", 14, "bold"))
btn_revert = tk.Button(button_frame2, text="Revert", command=lambda: (handle_button_press_duration("quit", 3), speed_scale.set(0)), width=30, bg="black", fg="white", font=("Arial", 14, "bold"))

# Grid layout for the buttons
btn_forward.grid(row=0, column=1, padx=5, pady=5)
btn_backward.grid(row=2, column=1, padx=5, pady=5)
btn_left.grid(row=1, column=0, padx=5, pady=5)
btn_right.grid(row=1, column=2, padx=5, pady=5)
btn_stop.grid(row=1, column=1, pady=5)
btn_revert.grid(row=0, column=1, padx=1, pady=1)

# Creating a scale widget for adjusting the speed
speed_scale = tk.Scale(window, from_=0, to=255, orient=tk.HORIZONTAL, length=300, bg="black")
speed_scale.set(current_speed)
speed_scale.pack(padx=10)

lbl_msg = tk.Label(window, text="Speed Control", font=("Arial", 14, "bold"), fg="black", bg="grey")
lbl_msg.pack()

# Creating a frame to hold the buttons
button_frame3 = tk.Frame(window, bg="orange")
button_frame3.pack(pady=10)

btn_forward_4 = tk.Button(button_frame3, text="Forward-4", command=lambda: handle_button_press_duration("forward", 4), width=10, bg="purple", fg="white", font=("Arial", 14, "bold"))
btn_right_5 = tk.Button(button_frame3, text="Right-5", command=lambda: handle_button_press_duration("right", 5), width=10, bg="magenta", fg="white", font=("Arial", 14, "bold"))

# Grid layout for the buttons
btn_forward_4.grid(row=1, column=0, padx=5, pady=5)
btn_right_5.grid(row=1, column=2, padx=5, pady=5)

# Define a function to update the current speed
def update_speed(value):
    global current_speed
    current_speed = int(value)
    handle_button_press_duration("speed", current_speed)

# Configure the scale widget to call the update_speed function when the value changes
speed_scale.configure(command=update_speed)

# Creating a frame to hold the labels and entry fields for custom run time and direction
custom_input_frame = tk.Frame(window, bg="grey")
custom_input_frame.pack(pady=10)

# Creating a label and entry widget for custom run time
lbl_custom_time = tk.Label(custom_input_frame, text="Run Time (sec):", font=("Arial", 10, "bold"), fg="black", bg="grey")
lbl_custom_time.grid(row=0, column=0, padx=5)

entry_custom_time = tk.Entry(custom_input_frame, font=("Arial", 14))
entry_custom_time.grid(row=0, column=1, padx=5)

# Creating a label and entry widget for custom run direction
lbl_direction = tk.Label(custom_input_frame, text="Run Direction:", font=("Arial", 10, "bold"), fg="black", bg="grey")
lbl_direction.grid(row=0, column=2, padx=5)

entry_direction = tk.Entry(custom_input_frame, font=("Arial", 14))
entry_direction.grid(row=0, column=3, padx=5)

# Defining a function to handle custom button press
def handle_custom_button_press():
    direction = entry_direction.get()
    run_time = entry_custom_time.get()
    try:
        run_time = int(run_time)
        # Set the custom run flag
        global custom_run_active
        custom_run_active = True
        handle_button_press_duration(direction, run_time)
    except ValueError:
        # Handle the case when the user doesn't enter a valid integer
        print("|Invalid Entry|")
    # Clear the custom time and direction after custom run
    entry_custom_time.delete(0, tk.END)
    entry_direction.delete(0, tk.END)

# Creating the custom run button
btn_custom_run = tk.Button(button_frame3, text="Custom Run", command=handle_custom_button_press, width=20, bg="black", fg="white", font=("Arial", 14, "bold"))

# Grid layout for the custom run button
btn_custom_run.grid(row=1, column=1, padx=5, pady=5)

# Defining a flag variable to track custom run status
custom_run_active = False

# Defining a function to be executed when the GUI window is closed
def on_closing():
    revert_car()
    ser.close()
    window.destroy()

# Configuring the GUI window to call the on_closing function when closed
window.protocol("WM_DELETE_WINDOW", on_closing)

# Starting the GUI main loop
window.mainloop()