# CSPlane

Với mục đích đem đến cho các bạn một phương pháp giải trí hiệu quả sau những giờ học và làm việc căng thẳng, nhà phát hành xin giới thiệu sản phẩm CS Plane:

- Các chức năng:
  + Play: Phần chơi chính gồm các vật thể như máy bay đồng minh, máy bay địch, đạn, tên lửa,... và bảng tính điểm, thời gian với độ khó tăng dần theo thời gian
  + Leaderboard: Bảng xếp hạng theo thành tích điểm và thời gian
  + Setting: Thay đổi nền chơi trong Play và thay đổi nhạc
  + Tutorial: Hướng dẫn chơi 
  + Exit: Thoát khỏi trò chơi

- Cách mở trò chơi:
  + B1: Download file Project game về máy
  + B2: Giải nén file
  + B3: Mở file "CS Plane" vừa được giải nén
  + B4: Mở cmd trong file "CS Plane"
  + B5: Thử 1 trong các cách sau:
    + C1: Chạy dòng lệnh: g++ -Isource/include/SDL2 -Lsource/lib -o main *.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 
    + C2: Chạy dòng lệnh: mingw32-make compile
  + B6: Thử 1 trong các cách sau:
    + C1: Chạy dòng lệnh: “./main” 
    + C2: Chạy dòng lệnh: “./main.exe”
    + C3: Chạy dòng lệnh: mingw32-make run

- Phân công:
  + Sơn (trưởng nhóm): Code menu và các chức năng Leaderboard, Setting, Tutorial, Exit 
  + Quang: Code phần Play và làm file README.md
