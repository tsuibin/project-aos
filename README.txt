2015.3.20
/*
桌面入口协议由AOS私有标准修改为 Desktop Entry Specification 1.0 标准
http://standards.freedesktop.org/desktop-entry-spec/desktop-entry-spec-1.0.html

新增
systemEnvironmentDesktopPath

*/

AppOS 私有标准说明

需要在系统根目录下创建

/Application
所有的应用程序都放在该目录下
结构如下：
/Application/
├── AppBrowser
├── AppCalculator
├── AppCamera
├── AppClock
├── AppContacts
├── AppDownloadManger
├── AppFaceBook
├── AppGoogleMap
├── AppGoogleSearch
├── AppMessage
├── AppMusicPlayer
├── AppNano
├── AppNote
├── AppSetting
├── AppTVGuide
├── AppWeather
└── AppYoutube

应用程序所使用的文件必须放在 App+程序名 的目录中，严格区分大小；
应用程序图标命名格式为： 应用程序名+.png；

