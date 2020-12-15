package com.darius.fourdmortalcombat

import com.badlogic.gdx.Gdx
import com.badlogic.gdx.graphics.Texture
import com.badlogic.gdx.graphics.g2d.SpriteBatch
import com.badlogic.gdx.graphics.g2d.TextureRegion

class Hero(image: Texture): Actor() {
    /*
        0 - stand
        1 - run
        2 - attack 1
        3 - attack 2 (TODO)
        4 - dodge
     */
    private var control: Control = Control(this)

    init{
        Gdx.input.inputProcessor = control
        scale = 4f
        framesAmount = listOf(13, 7, 4, 3, 7)
        frameY = listOf(460, 760, 45, -1, 1065)
        frameWidth = listOf(34, 33, 58, -1, 32)
        frameOffset = listOf(15, 16, 15, -1, 14)
        frameTime = listOf(0.05, 0.035, 0.035, -1.0, 0.035)
        leftOffset = 30
        frames = mutableListOf( mutableListOf(), mutableListOf(), mutableListOf(), mutableListOf(), mutableListOf() )

        for (j in 0 .. 4) {
            if(j == 3)
                continue
            for (i in 0..framesAmount[j])
                frames[j].add(TextureRegion(image, leftOffset + frameWidth[j] * i + frameOffset[j] * i, frameY[j], frameWidth[j], frameHeight))
        }

        currentFrame = frames[0][0]
        currentFrameNumber = 0
        currentFrameTime = 0.0
        currentAnimation = 0
        direction = 1
        x = screenWidth/2f
        y = 0f
    }

    override fun update(batch: SpriteBatch, delta: Float) {
        draw(batch)
        currentFrameTime += delta
        if (currentFrameTime > frameTime[currentAnimation]){
            currentFrameTime = 0.0
            currentFrameNumber = if (currentFrameNumber + 1 == framesAmount[currentAnimation]) 0 else currentFrameNumber + 1
            if (currentFrameNumber == 0 && currentAnimation > 1)
                currentAnimation = 0
            currentFrame = frames[currentAnimation][currentFrameNumber]
        }
        when (currentAnimation) {
            1 -> speed = 5
            4 -> speed = 20
            else -> speed = 0
        }
        x += speed * direction
        if (currentFrame.isFlipX && direction == 1 || !currentFrame.isFlipX && direction == -1)
            currentFrame.flip(true, false)
    }

    override fun draw(batch: SpriteBatch) {
        val mode = 0
        val fixedAnimation = 4
        when(mode){
            0 -> batch.draw(currentFrame, x, y, frameWidth[currentAnimation] * screenHeight/scale/frameHeight,screenHeight/scale)
            1 ->{ // all frames
                for (i in 0 .. framesAmount[fixedAnimation])
                    batch.draw(frames[fixedAnimation][i], x + (frameWidth[fixedAnimation] + 120) * i, y,
                            frameWidth[fixedAnimation] * screenHeight/scale/frameHeight,screenHeight/scale)
            }
        }
    }

    fun isAttacking(): Boolean {
        return when (currentAnimation) {
            2 -> true
            else -> false
        }
    }

    fun touch (x: Int, y:Int){
        if (currentAnimation > 1)
            return
        when (x) {
            in 0..screenWidth/4 -> {
                direction = -1
                if(currentAnimation != 1) {
                    currentFrameNumber = 0
                    currentFrameTime = 0.0
                    currentAnimation = 1
                }
            }
            in screenWidth/4..screenWidth/2 -> {
                direction = 1
                if(currentAnimation != 1) {
                    currentFrameNumber = 0
                    currentFrameTime = 0.0
                    currentAnimation = 1
                }
            }
            in screenWidth / 4 * 3..screenWidth -> {
                if(y > screenHeight/2) {
                    if (currentAnimation != 2) {
                        currentFrameNumber = 0
                        currentFrameTime = 0.0
                        currentAnimation = 2
                    }
                }
                else
                    if(currentAnimation != 4) {
                        currentFrameNumber = 0
                        currentFrameTime = 0.0
                        currentAnimation = 4
                    }
            }
            else-> {
                currentAnimation = 0
            }
        }
    }
}