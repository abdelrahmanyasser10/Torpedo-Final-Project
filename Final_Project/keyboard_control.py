import keyboard
import socket
import time

# Our Main Function
def main():
    client_socket = setting_client()
    keyboard_control(client_socket)
    


# Setting the client connection to the ESP32 server
def setting_client():
    # set up a socket
    Host = '192.168.4.1'
    Port = 8080
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Connecting to the ESP32
    sock.connect((Host, Port))
    return sock


# Control the car from the keyboard
def keyboard_control(client_socket):
    flag = False
    while True:
        # Move Forward
        if keyboard.is_pressed("w"):
            print("w")
            order = "f"
            client_socket.send(order.encode())
            flag = True
        # Move Backward
        elif keyboard.is_pressed("s"):
            print("s") 
            order = "b"
            client_socket.send(order.encode())
            flag = True
        # Turn Right
        elif keyboard.is_pressed("d"):
            print("d") 
            order = "r"
            client_socket.send(order.encode())
            flag = True
        # Turn Left
        elif keyboard.is_pressed("a"):
            print("a") 
            order = "l"
            client_socket.send(order.encode())
            flag = True
        # hitting the breaks
        elif keyboard.is_pressed("space"):
            print("Stop")
            order = "s"
            client_socket.send(order.encode())
        # Set Servo angle to 0
        elif keyboard.is_pressed("0"):
            print("0")
            angle = "0"
            client_socket.send(angle.encode())
        # Set Servo angle to 45
        elif keyboard.is_pressed("1"):
            print("1")
            angle = "1"
            client_socket.send(angle.encode())
        # Set Servo angle to 90
        elif keyboard.is_pressed("2"):
            print("2")
            angle = "2"
            client_socket.send(angle.encode())
        # Set Servo angle to 135
        elif keyboard.is_pressed("3"):
            print("3")
            angle = "3"
            client_socket.send(angle.encode())
        # Set Servo angle to 180
        elif keyboard.is_pressed("4"):
            print("4")
            angle = "4"
            client_socket.send(angle.encode())
        elif keyboard.is_pressed("5"):
            print("5")
            angle = "5"
            client_socket.send(angle.encode())
        elif keyboard.is_pressed("6"):
            print("6")
            angle = "6"
            client_socket.send(angle.encode())
        elif keyboard.is_pressed("7"):
            print("7")
            angle = "7"
            client_socket.send(angle.encode())
        elif keyboard.is_pressed("8"):
            print("8")
            angle = "8"
            client_socket.send(angle.encode())
        elif keyboard.is_pressed("9"):
            print("9")
            angle = "9"
            client_socket.send(angle.encode())
        # break the loop
        elif keyboard.is_pressed("escape"):
            break
        elif keyboard.is_pressed("shift"):
            print("shift")
            order = "i"
            client_socket.send(order.encode())
        # Stop the car
        else:
            if flag:
                print("STOP")
                order = "s"
                client_socket.send(order.encode())
                flag = False
        # Control the Sensitivity and response of the keyboard
        time.sleep(0.06)

if __name__ == "__main__":
    main()