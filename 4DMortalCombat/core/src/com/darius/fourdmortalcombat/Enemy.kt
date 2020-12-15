package com.darius.fourdmortalcombat

import com.badlogic.gdx.graphics.Texture
import com.badlogic.gdx.graphics.g2d.SpriteBatch
import com.badlogic.gdx.graphics.g2d.TextureRegion

class Enemy(image: Texture, side: Boolean): Actor() {
    /*
        0 - run
        1 - dead
     */
    var dead: Boolean = false
    init{
        scale = 6f
        framesAmount = listOf(7, 2)
        frameY = listOf(770, 1283)
        frameWidth = listOf(34, 43)
        frameOffset = listOf(15, 1)
        frameTime = listOf(0.035, 0.6)
        leftOffset = 30
        frames = mutableListOf(mutableListOf(), mutableListOf())
        frameHeight = 34
        for (j in 0 .. 1) {
            for (i in 0..framesAmount[j])
                when (j){
                    0 -> frames[j].add(TextureRegion(image, leftOffset + frameWidth[j] * i + frameOffset[j] * i, frameY[j], frameWidth[j], frameHeight))
                    1 -> frames[j].add(TextureRegion(image, leftOffset, frameY[j], 43, 17))
                }
        }
        currentFrame = frames[0][0]
        currentFrameNumber = 0
        currentFrameTime = 0.0
        currentAnimation = 0
        when (side){
            true -> {
                direction = 1
                x = - frameWidth[0] * 2f
            }
            false -> {
                direction = -1
                x = screenWidth + frameWidth[0] * 2f
            }
        }
        y = 40f
    }
    override fun update(batch: SpriteBatch, delta: Float) {
        if(dead) return
        draw(batch)
        currentFrameTime += delta
        if (currentFrameTime > frameTime[currentAnimation]){
            currentFrameTime = 0.0
            currentFrameNumber = if (currentFrameNumber + 1 == framesAmount[currentAnimation]) 0 else currentFrameNumber + 1
            if (currentFrameNumber == 0 && currentAnimation > 0)
                dead = true
            currentFrame = frames[currentAnimation][currentFrameNumber]
        }
        when (currentAnimation){
            0 -> speed = 3
            else -> speed = 0
        }
        x += speed * direction
        if (currentFrame.isFlipX && direction == 1 || !currentFrame.isFlipX && direction == -1)
            currentFrame.flip(true, false)
    }

    override fun draw(batch: SpriteBatch) {
        val mode = 0
        val fixedAnimation = 1
        when(mode){
            0 -> batch.draw(currentFrame, x, y, frameWidth[currentAnimation] * screenHeight/scale/frameHeight,screenHeight/scale)
            1 ->{ // all frames
                for (i in 0 .. framesAmount[fixedAnimation])
                    batch.draw(frames[fixedAnimation][i], x + (frameWidth[fixedAnimation] + 120) * i, y,
                            frameWidth[fixedAnimation] * screenHeight/scale/frameHeight,screenHeight/scale)
            }
        }
    }

    fun kill(){
        currentAnimation = 1
        currentFrameNumber = 0
        currentFrameTime = 0.0
    }
}