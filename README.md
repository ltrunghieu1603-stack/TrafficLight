# Hệ thống Điều khiển Đèn Giao Thông Thông Minh 

## 1. Thành viên nhóm
- **Lê Trung Hiếu** - MSSV: 2410989


## 2. Cấu trúc dự án
- `Core/Inc` & `Core/Src`:
  - `scheduler.h/.c`: Bộ lập lịch hợp tác (Cooperative Scheduler) sử dụng Delta Queue đạt độ phức tạp $O(1)$ với tick 10ms (`TIM2`).
  - `software_timer.h/.c`, `button.h/.c`, `traffic_light.h/.c`, `lcd.h/.c`, `dht20.h/.c`: Lớp Driver giao tiếp phần cứng (HAL).
  - `fsm_automatic.h/.c`, `fsm_manual.h/.c`, `fsm_tuning.h/.c`, `global.h/.c`: Lớp máy trạng thái hữu hạn (FSM) điều khiển logic nghiệp vụ.
- `BTL_TrafficLight.ioc`: File cấu hình chân và ngoại vi STM32CubeMX (`NUCLEO-F103RB`).

## 3. Hướng dẫn Build & Nạp code
1. Clone repository về máy và mở bằng **STM32CubeIDE** (`File -> Open Projects from File System...`).
2. Cấu hình Debug: Chọn mạch nạp **ST-LINK (OpenOCD)**, giao tiếp **Serial Wire (SWD)**.
3. Nhấn `Ctrl + B` để Build và `Run` để nạp firmware xuống kit `XNUCLEO-F103RB`.

## 4. Hướng dẫn vận hành 4 nút nhấn
- **`BTN_0` (PA8):** Chuyển đổi tuần tự giữa 3 chế độ: `AUTO` $\rightarrow$ `MANUAL` $\rightarrow$ `TUNING` $\rightarrow$ `AUTO`.
- **`BTN_1` (PA9):** Đảo pha đèn trực tiếp (trong chế độ `MANUAL`) hoặc chuyển loại đèn cần chỉnh `RED` $\rightarrow$ `AMBER` $\rightarrow$ `GREEN` (trong chế độ `TUNING`).
- **`BTN_2` (PC7):** Tăng thời gian sáng của đèn đang chọn thêm `1 giây` (trong chế độ `TUNING`).
- **`BTN_3` (PB6):** Giảm thời gian sáng của đèn đang chọn đi `1 giây` (trong chế độ `TUNING`).
