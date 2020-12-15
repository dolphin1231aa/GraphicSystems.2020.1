package com.darius.fourdmortalcombat

import com.badlogic.gdx.graphics.g2d.SpriteBatch
import com.badlogic.gdx.Gdx
import com.badlogic.gdx.Screen
import com.badlogic.gdx.graphics.GL20
import com.badlogic.gdx.graphics.Texture
import kotlin.math.abs
import kotlin.random.Random

class World : Screen {
    private val screenHeight = Gdx.graphics.height
    private val screenWidth = Gdx.graphics.width

    lateinit var batch: SpriteBatch
    private lateinit var background: Texture
    private lateinit var hero: Hero
    private lateinit var enemy: Texture
    private var enemies: MutableList<Enemy>? = null
    private var aliveEnemies: Int = 0

    override fun show() {
        batch = SpriteBatch()
        background = Texture ("background.png")
        val temp = Texture("hero.png")
        enemy = Texture("enemy.png")
        hero = Hero(temp)
        enemies = mutableListOf()
    }

    override fun render(delta: Float) {
        Gdx.gl.glClearColor(0f, 0f, 0f, 1f)
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT)
        fightControl()
        batch.begin()
        batch.draw(background,0f,0f,background.width * screenHeight/background.height.toFloat(), screenHeight.toFloat())
        hero.update(batch, delta)
        for (i in enemies!!)
            i.update(batch, delta)
        batch.end()
    }

    private fun fightControl(){
        for (i in enemies!!){
            if (i.dead) {
                continue
            }
            if (!hero.isAttacking()) break
            if (i.direction == 1 && i. x > screenWidth + 20 || i.direction == -1 && i.x < - 100 || abs(hero.x - i.x) < 100) {
                i.kill()
                aliveEnemies--
            }
        }
        if (aliveEnemies < 3 && Random.nextDouble(0.0,1.0) < 0.02 ) {
            enemies!!.add( Enemy(enemy, Random.nextDouble(0.0, 1.0) < 0.5) )
            aliveEnemies++
        }
    }

    override fun resize(width: Int, height: Int) { }

    override fun pause() { }

    override fun resume() { }

    override fun hide() { }

    override fun dispose() { }
}