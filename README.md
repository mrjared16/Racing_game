# Racing_game
Đồ án kỹ thuật lập trình
- FILE:
  + Level.xlsx: Chi tiết về level cũng như sự thay đổi các yếu tố tạo nên độ khó trong game
- Change:
  - Chia nhỏ file, đổi khá nhiều tên hàm và biến, tổ chức lại một số hàm.
  - Gộp thành hàm showMenu, thêm nút back.
  - Thay đổi một số chi tiết cấu trúc vật cản, đạn.
  - Test đạn, chưa chính thức.
  - Fix một số bug.
  - Thêm coin.
  - Thêm cấu trúc item : gồm tiền, đạn, vv.
  - Thêm hàm chance (ở function.h) để tiện sử dụng cơ chế ngẫu nhiên (sinh item, coin, vật cản, ...).
  - Sửa bug với item khi remove (checkvitri).
  - Sửa bug khi điểm vượt quá 68 (khi sleep_time âm phát sinh lỗi vì nó là unsigned).
  - Thay đổi hàm di chuyển khi nhận phím để tiện viết tự động hóa.
  - Hoàn thiện item hóa tiền.
  - Thêm hàm kiểm tra tọa độ có trong map, chỉnh sửa tất cả điều kiện về tọa độ thành hàm.
  - Thêm level cho game, tạo độ khó cho game từ 5 yếu tố:
    + Thời gian nghỉ.
    + Số vật cản tối đa.
    + Tỉ lệ ra vật cản.
    + Biên độ dao động của vật cản.
    + Tỉ lệ dao động của vật cản.
  - Sửa tên hàm, tên biến
  - Sửa giao diện
  - Thêm âm thanh
