@echo off
title Sistema de Gestion de Flota de Vehiculos Electricos
cls
python flota_vehiculos.py
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [Error] No se pudo ejecutar Python.
    echo Asegurate de tener Python instalado y agregado al PATH de Windows.
    echo.
)
pause
