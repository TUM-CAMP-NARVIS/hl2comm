#------------------------------------------------------------------------------
# This script receives encoded video from the HoloLens depth camera in ahat
# mode and plays it. The resolution is 512x512 @ 45 FPS. The stream supports 
# three operating modes: 0) video, 1) video + rig pose, 2) query calibration
# (single transfer). Press esc to stop. Depth and AB data are scaled for
# visibility.
#------------------------------------------------------------------------------
# Warning: starting the rm depth ahat stream while the pv subsystem is on
# will put the ahat stream in an unrecoverable state
# https://github.com/microsoft/HoloLens2ForCV/issues/133

from pynput import keyboard

import numpy as np
import hl2ss
import cv2

# Settings --------------------------------------------------------------------

# HoloLens address
host = "192.168.1.7"

# Port
port = hl2ss.StreamPort.RM_DEPTH_AHAT

# Operating mode
# 0: video
# 1: video + rig pose
# 2: query calibration (single transfer)
mode = hl2ss.StreamMode.MODE_1

#------------------------------------------------------------------------------

hl2ss.stop_subsystem_pv(host, hl2ss.StreamPort.PERSONAL_VIDEO)
rc_control = hl2ss.tx_rc(host, hl2ss.IPCPort.REMOTE_CONFIGURATION)
while (rc_control.get_pv_subsystem_status()):
    pass

if (mode == hl2ss.StreamMode.MODE_2):
    data = hl2ss.download_calibration_rm_depth_ahat(host, port)
    print('Calibration data')
    print(data.uv2xy.shape)
    print(data.extrinsics)
    print(data.scale)
    print(data.alias)
    print(data.undistort_map.shape)
    print(data.intrinsics)
    quit()

enable = True

def on_press(key):
    global enable
    enable = key != keyboard.Key.esc
    return enable

listener = keyboard.Listener(on_press=on_press)
listener.start()

client = hl2ss.rx_decoded_rm_depth_ahat(host, port, hl2ss.ChunkSize.RM_DEPTH_AHAT, mode, hl2ss.VideoProfile.H264_BASE, 8*1024*1024)
client.open()

while (enable):
    data = client.get_next_packet()
    print('Pose at time {ts}'.format(ts=data.timestamp))
    print(data.pose)
    cv2.imshow('Depth', data.payload.depth / np.max(data.payload.depth))
    cv2.imshow('AB', data.payload.ab / np.max(data.payload.ab))
    cv2.waitKey(1)

client.close()
listener.join()
