solution "nart"

local PROJ_DIR = path.getabsolute("..")

configurations { "Debug", "Release" }

location(path.join(PROJ_DIR, "build"))
targetdir(path.join(PROJ_DIR, "bin"))

dofile "nart.lua"
