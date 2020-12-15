package com.darius.fourdmortalcombat

import com.badlogic.gdx.Game

class Launcher: Game() {
    override fun create() {
        setScreen(World())
    }
}