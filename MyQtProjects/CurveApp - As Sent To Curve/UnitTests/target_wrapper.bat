@echo off
SetLocal EnableDelayedExpansion
(set PATH=C:\Qt57\5.7\msvc2013_64\lib;!PATH!)
if defined QT_PLUGIN_PATH (
    set QT_PLUGIN_PATH=C:\Qt57\5.7\msvc2013_64\plugins;!QT_PLUGIN_PATH!
) else (
    set QT_PLUGIN_PATH=C:\Qt57\5.7\msvc2013_64\plugins
)
%*
EndLocal
