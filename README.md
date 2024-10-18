# IPC_signal

2 files trong repo này độc lập, không liên quan với nhau

1. signal_CTRL_C.cpp
- gửi signal từ tiến trình cha đến tiến trình con (CTRL_C: kết thúc tiến trình)
- tiến trình con khi nhận được signal từ tiến trình cha có thể xử lý theo default action (kết thúc tiến trình), hoặc dựa vào hàm được đăng ký trước đó (sig_handler)
- sig_handler chỉ in ra dòng lệnh, nên tiến trình con sẽ không kết thúc tiến trình

2. signal_parent_child.cpp
- tiến trình cha gửi các signal là SIGSTOP (tạm dừng tiến trình), và SIGCONT (tiếp tục tiến trình) đến tiến trình con
- tiến trình con nhận được các signal
- đối với SIGSTOP, tiến trình con bắt buộc xử lý theo default action (vì SIGSTOP không thể được catch hoặc ignore)
- với SIGCONT, tiến trình con in ra thông báo tiếp tục thực thi tiến trình
