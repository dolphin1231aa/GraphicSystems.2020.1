package com.darius.fourdmortalcombat

import com.badlogic.gdx.Gdx
import com.badlogic.gdx.InputProcessor

class Control (var actor: Hero): InputProcessor {
    val screenHeight = Gdx.graphics.height
    val screenWidth = Gdx.graphics.width

    override fun touchDown(screenX: Int, screenY: Int, pointer: Int, button: Int): Boolean {
        actor.touch(screenX, screenHeight - screenY)
        return true
    }

    override fun keyDown(keycode: Int): Boolean {
        return false
    }

    override fun keyUp(keycode: Int): Boolean {
        return false
    }

    override fun keyTyped(character: Char): Boolean {
        return false
    }

    override fun touchUp(screenX: Int, screenY: Int, pointer: Int, button: Int): Boolean {
        return false
    }

    override fun touchDragged(screenX: Int, screenY: Int, pointer: Int): Boolean {
        return false
    }

    override fun mouseMoved(screenX: Int, screenY: Int): Boolean {
        return false
    }

    override fun scrolled(amountX: Float, amountY: Float): Boolean {
        return false
    }
}