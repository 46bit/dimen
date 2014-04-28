# Dimen
Fractal generation.

## Install
```
make
```

## Dragon Curve
Outputs turtle commands to render the [Dragon Curve Fractal](http://en.wikipedia.org/wiki/Dragon_curve). Run and rasterise to `chelonian.png` with:

```
./bin/dragon_curve | ./bin/chelonian
```

## Gosper Curve
Outputs turtle commands to render the [Gosper Curve Fractal](https://en.wikipedia.org/wiki/Gosper_curve). Run and rasterise to `chelonian.png` with:

```
./bin/gosper_curve | ./bin/chelonian
```

## Mandelbrot
Directly render the [Mandelbrot Set Fractal](https://en.wikipedia.org/wiki/Mandelbrot_set) to `mandelbrot.png` with:

```
./bin/mandelbrot
```

## Chelonian
A basic turtle rasterizer. Input commands via stdin, provide output image filename as argument. This aims to center the drawing in order to ensure maximum visibility.

### Commands
`RT 45` to turn right 45°.

`LT 45` to turn left 45°.

`FD 4` to go forward 4 units.
