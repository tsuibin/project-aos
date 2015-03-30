2015.3.20
/*
桌面入口协议由AOS私有标准修改为 Desktop Entry Specification 1.0 标准
http://standards.freedesktop.org/desktop-entry-spec/desktop-entry-spec-1.0.html

Example Desktop Entry File

[Desktop Entry]
Version=1.0
Type=Application
Name=Foo Viewer
Comment=The best viewer for Foo objects available!
TryExec=fooview
Exec=fooview %F
Icon=fooview.png
MimeType=image/x-foo;
X-KDE-Library=libfooview
X-KDE-FactoryName=fooviewfactory
X-KDE-ServiceType=FooService




Icon 协议修改为
http://standards.freedesktop.org/icon-theme-spec/icon-theme-spec-latest.html

Directory Layout

Icons and themes are looked for in a set of directories. By default, apps should look in $HOME/.icons (for backwards compatibility), in $XDG_DATA_DIRS/icons and in /usr/share/pixmaps (in that order). Applications may further add their own icon directories to this list, and users may extend or change the list (in application/desktop specific ways).In each of these directories themes are stored as subdirectories. A theme can be spread across several base directories by having subdirectories of the same name. This way users can extend and override system themes.

In order to have a place for third party applications to install their icons there should always exist a theme called "hicolor" [1]. The data for the hicolor theme is available for download at: http://www.freedesktop.org/software/icon-theme/. Implementations are required to look in the "hicolor" theme if an icon was not found in the current theme.

Each theme is stored as subdirectories of the base directories. The internal name of the theme is the name of the subdirectory, although the user-visible name as specified by the theme may be different. Hence, theme names are case sensitive, and are limited to ASCII characters. Theme names may also not contain comma or space.

In at least one of the theme directories there must be a file called index.theme that describes the theme. The first index.theme found while searching the base directories in order is used. This file describes the general attributes of the theme.

In the theme directory are also a set of subdirectories containing image files. Each directory contains icons designed for a certain nominal icon size, as described by the index.theme file. The subdirectories are allowed to be several levels deep, e.g. the subdirectory "48x48/apps" in the theme "hicolor" would end up at $basedir/hicolor/48x48/apps.

The image files must be one of the types: PNG, XPM, or SVG, and the extension must be ".png", ".xpm", or ".svg" (lower case). The support for SVG files is optional. Implementations that do not support SVGs should just ignore any ".svg" files. In addition to this there may be an additional file with extra icon-data for each file. It should have the same basename as the image file, with the extension ".icon". e.g. if the icon file is called "mime_source_c.png" the corresponding file would be named "mime_source_c.icon".

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

