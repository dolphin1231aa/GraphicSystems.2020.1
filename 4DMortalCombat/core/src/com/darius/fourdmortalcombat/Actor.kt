package com.darius.fourdmortalcombat

import com.badlogic.gdx.Gdx
import com.badlogic.gdx.graphics.g2d.SpriteBatch
import com.badlogic.gdx.graphics.g2d.TextureRegion

abstract class Actor() {
    val screenHeight = Gdx.graphics.height
    val screenWidth = Gdx.graphics.width

    lateinit var frames: MutableList<MutableList<TextureRegion>>
    lateinit var framesAmount: List<Int>
    var currentFrameTime: Double = 0.0
    var currentFrameNumber: Int = 0
    lateinit var currentFrame: TextureRegion
    var currentAnimation: Int = 0
    lateinit var frameY: List<Int>
    lateinit var frameWidth: List<Int>
    lateinit var frameOffset: List<Int>
    var frameHeight: Int = 50
    lateinit var frameTime: List<Double>
    var leftOffset: Int = 0

    var direction = 1
    var speed: Int = 0
    var x: Float = 0f
    var y: Float = 0f
    var scale = 0f

    init{ }

    abstract fun update(batch: SpriteBatch, delta: Float)
    abstract fun draw(batch: SpriteBatch)
}