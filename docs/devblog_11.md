[Dev blog](devblog.md) | [Project aims and goals](goals.md) | [Project to-do](todo.md) | [Youtube playlist](https://www.youtube.com/watch?v=8m7peVlW2mE&list=PLJqFvAhkcSkkks42zClG5WlvO1khFZCKK) | [KTANE IRL Discord server](https://discord.com/channels/711013430575890432)

---

# Dev blog
I'm currently making short update videos on progress on [my Youtube playlist](https://www.youtube.com/watch?v=8m7peVlW2mE&list=PLJqFvAhkcSkkks42zClG5WlvO1khFZCKK). It's certainly much quicker to film/narrate what's new than type up a new blog post! Check there for more up-to-date info, meanwhile a more detailed write-up will appear here going into much more detail.

---

[Prev post: Let's get physical](devblog_10.md)

## 2022/05/01 - Coding Passwords and Morse
Again - playing catch-up with progress - this post covers progress in June to July 2021.

Well this isn't the case as promised at the end of the last post! I had designed the case and sent off for parts, but while I waited I managed to knock up two modules on the breadboards, so the case comes later!

### Passwords
This was a new module to code. Unlike th eprevious ones, I hadn't attempted this module on the old Arduino prototype so this was built from scratch.

A long time prior to coding this up, I had been digging around for electronics components to match the look of the game. In this case, I had a lot of fun looking at finding a matching GLCD (graphical LCD) to use for the main display.

> ![Passwords](https://i.imgur.com/oMkNBHf.jpg)
> 
> Passwords module after finding the right solution

Apart from the screen, the hardware just required 11 buttons to make this work. The ESP32 was running low on pins, but it was doable to hook each button to a pin. Instead of taking that easy route, I decided to try a keyboard matrix to handle the buttons as a little challenge. This was fairly straight-forward to wire up after looking at a few resources online, but I needed a whole second breadboard to fit the buttons...

> ![Passwords with matrix](https://i.imgur.com/hywiyue.jpg)
> 
> Passwords module with the button matrix

Moving on to the code, this was a tricky one. Tricky two actually...

The first issue was getting the letters on the display. Screens like these are supported by the great u8g2 library, however to save space (fonts can take a fair chunk of memory) I decided to manually draw the letters using 4x4 pixel boxes. This worked very quickly and I had great control over where the letters appeared on the display, so I could try to match the design of the game as much as possible.

The second issue was coding the game logic which determined the list of possible letters you can cycle though. In the game, there are 6 letters that can be selected for each of the 5 places in the displayed word. This list, however, must only contain one of the words from the accepted word list - the list of words in the manual that are must be entered to solve the module. I started with a full alphabet of possibilities in each of the 5 places, chose an accepted word which would be the solution to this game, then looped through each of the other accepted words and removed a letter from one of the places at random (thus removing the ability to input that word). But I needed to check that the letters I removed wren't in the selected accepted word, or another letter in another place would be picked to be removed. After eliminating the other accepted words, then more letters would be removed to get down to the 6 letters for each place. And lastly, another final check to make sure that the first possible letters that are initially shown on the screen are not the actual selected word (otherwise the puzzle would come pre-solved!) so this would need a shuffle.

### Morse
Another new module, this built off both the debugger and Simon so came together fairly quickly.

The blinky light is a simply LED, which needed difficult timings to be set up for each Morse letter. This is where the Simon code could be partially recycled to make this a little easier.

As for inputs, rather than the left and right buttons to select frequency, I opted to diverge from the game and instead use a rotary encoder. This felt like a reasonable choice, as this is a little more of a radio input, and the game was limited by its input methods so would eliminate the ability to use a rotary knob in-game. This was an easy copy from the debugger's code.

Lastly, the display. I used the u8g2 library to draw the lettering. To get the correct font as the game, I needed to go through a few steps to convert the font into a c data file which the library could then use. This was a little painful to do, and I had to do it a few times until I was happy with the size of the font.

> ![Morse](https://i.imgur.com/GYJXWpX.png)
> 
> Morse code testing

I didn't tackle the frequency select pointer, but pushed that into the future. I had some ideas but without having finalised the module boxes yet, it would have been premature to attempt this now.

Next I receive a delivery allowing me to start assembling the case...

[Prev post: Let's get physical](devblog_10.md)
