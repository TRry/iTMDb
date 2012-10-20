# iTMDb

iTMDb is an Objective-C Cocoa wrapper (framework) for the [TMDb.org](http://tmdb.org/) v2.1 API. © Christian Rasmussen, 2010–2012.

This software is dual-licensed (pick either one you want): **MIT License** or **New BSD License**. See the `LICENSE` file. If you would like to use a different license, please contact me.

iTMDb is developed for **Mac OS X** 10.7 Snow Leopard and OS X 10.8 Mountain Lion, but it should work fine with iOS 5 and up (though not tested — and the use of the Cocoa framework in the demo app will have to be replaced with Cocoa Touch).

**You need Xcode 4.5 and LLVM Clang 4.1 to build the project.**

Please remember to read the TMDb API [Terms of Use](http://api.themoviedb.org/2.1/terms-of-use).

You can safely submit your apps using iTMDb to the App Store (it's been approved for use with [Collection](http://collectionapp.com/)).

## Discontinuation notice

Development of this project has more or less stopped, and no major work on it will be made. It is, however, still working and is useful if you need movie, cast and crew information from TMDb.

Since the release of this framework, TMDb has a newer API, [version 3](http://docs.themoviedb.apiary.io/), that they encurage developers to use instead of version 2.1, which this framework uses.

## Documentation

Most of the classes are documented using [appledoc](https://github.com/tomaz/appledoc). A generated copy of the documentation can be found [here](http://docs.apoltix.com/itmdb/).

Certain classes have no specific documentation, but they are internal classes used by other classes, and are not intended to be interacted with directly.

The framework was built to be as easy and intuitive to use, so looking at the header files should give you an idea of how it is structured. Please see the test application (available in the Xcode project) for code samples.

## How to use

You can check out the included test project (`iTMDbTest`) within the Xcode workspace for an example of how to use the framework. All iTMDb classes are prefixed with `TMDB`, and the main class, from which most common operations can be made, just called `TMDB`, is known as the "context".

1. Add the framework to your project like any other framework (use Google if you don't know how to do this).

2. Add the following line to the header (or source) files where you will be using iTMDb:

	``` objective-c
	 #import <iTMDb/iTMDb.h>
	```

3. You create an instance of iTMDb like this. Replace ``api_key`` with your own API key, provided by [TMDb](http://api.themoviedb.org/). iTMDb performs fetch requests asynchronously, so setting a delegate is required. The delegate will receive notifications when the loading is done. The object should follow the TMDBDelegate protocol.

	``` objective-c
	TMDB *tmdb = [[TMDB alloc] initWithAPIKey:@"api_key" delegate:self];
	```

4. Look up a movie (while knowing it's id).

	``` objective-c
	[tmdb movieWithID:22538];
	```

5. An API request is made. Once information has been downloaded, the context object (`tmdb`) will receive a notification. The fetched properties are available through the returned object, which is sent to the context delegate (`tmdb.delegate`) with the following method:

	``` objective-c
	-[tmdb:(TMDB *)context didFinishLoadingMovie:(TMDBMovie *)movie]
	```

	Set the movie's title to a text field:

	``` objective-c
	-[movieTitleTextField setStringValue:movie.title];
	```

## ARC Support

iTMDb was originally developed using classic retain/release, but it has since switched to using ARC. There is no support for garbage collection.

If you need to integrate the source directly into your project that is not using ARC, you can specify the ``-fobjc-arc`` compiler flag for each ``.m`` file in the *Compile Sources* section of the *Build Phases* tab of the target.

## What's missing

iTMDb does not yet cover the entire TMDb API, but movie search and lookup works. Things like authentication is not implemented.

If you are up for it, feel free to develop on the framework and submit a pull request.