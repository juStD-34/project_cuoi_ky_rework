# project_cuoi_ky_rework


1. Hướng dẫn cài đặt :
  - Fork về your repo
  - Dùng lệnh git clone "...." (đường link đến repo)
  - Copy file SDL vào trong máy, lấy đường link dẫn đến folder include và lib để dùng vào lệnh dịch
  - Mở file chạy lệnh trong cmd :
       g++ main.cpp src/Ball.cpp src/renderTexture.cpp src/Button.cpp src/init.cpp -ID:\dev-lib\i686-32bit\include\SDL2 -LD:\dev-lib\i686-32bit\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer  -o main.exe;
   - Chạy file main.exe
2. Mô tả chung về trò chơi :
  - Người chơi điều khiển quá bóng sao cho bóng bay vào lỗ, 
  - Mỗi lần bóng đập tường người chơi được 100 điểm, khi kết thúc lượt bắn sẽ bị trừ 200 điểm. 
3. Mô tả các chức năng :
  - Cài màn hình chính
  ![image](https://user-images.githubusercontent.com/91711287/169048019-4d5c730e-30f8-487e-927c-69f5187263bc.png)
  - Cài logic bật nảy cho game bằng góc angle
  - Render màn hình bắt đầu game, end game, chức năng restart,...
  - ![image](https://user-images.githubusercontent.com/91711287/169046259-a4f6429e-8f87-4776-9ce7-432b7850ad4e.png)
  - ![image](https://user-images.githubusercontent.com/91711287/169048325-1868df1a-38f8-477c-8d05-35393ba76e4c.png)
  - ![image](https://user-images.githubusercontent.com/91711287/169048464-0f2fac4c-2914-4a97-be10-92910a8f6c4b.png)



4. Các kỹ thuật lập trình
  - Dùng class
  - Chia file, tổ chức code, chỉnh code
  - Sử dụng đồ họa SDL2
  - ...
  - 
5.Kết luận
  - Điều tâm đắc : đã tự suy nghĩ, vận dụng các kiến thức học được trong khóa lập trình nâng cao và kết hợp với việc học về đồ họa để tạo nên 1 game cơ bản 
  - Học thêm được nhiều tính năng, sử dụng tốt hơn SDL, chia file và sử dụng hợp lý việc chia file
  - Hướng phát triển :
    + Tạo chế độ 2 người chơi 
    + Thêm class Wall để tạo bản đồ gồm nhiều tường
    + Chuyển lực từ điểm thành Vector để tính được hướng và thêm tính năng lực
