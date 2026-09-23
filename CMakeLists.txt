# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr 4.2.0 REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(pcd8544_sample_app)

target_sources(app PRIVATE src/main.c)
