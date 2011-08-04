//
//  URLDownloader.h
//  iOS-URLDownloader
//
//  Created by Kristijan Sedlak on 7/21/11.
//  Copyright 2011 AppStrides. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "URLCredential.h"

@class URLDownloader;


#pragma mark -

typedef enum
{
	URLDownloaderStateInactive = 0,
	URLDownloaderStateConnecting = 1,
	URLDownloaderStateAuthenticating = 2,
	URLDownloaderStateStarted = 3,
	URLDownloaderStateDownloading = 4,
	URLDownloaderStateFinished = 5,
	URLDownloaderStateCanceled = 6
} 
URLDownloaderState;


#pragma mark -

@protocol URLDownloaderDelegate <NSObject>

@required
- (void)urlDownloader:(URLDownloader *)downloader didFinishWithData:(NSData *)data;
- (void)urlDownloader:(URLDownloader *)downloader didFailOnAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;
- (void)urlDownloader:(URLDownloader *)downloader didFailWithError:(NSError *)error;
- (void)urlDownloader:(URLDownloader *)downloader didFailWithNotConnectedToInternetError:(NSError *)error;

@optional
- (void)urlDownloader:(URLDownloader *)downloader didReceiveData:(NSData *)data;
- (void)urlDownloader:(URLDownloader *)downloader didChangeState:(URLDownloaderState)state;

@end


#pragma mark -

@interface URLDownloader : NSObject
{
    id <URLDownloaderDelegate> delegate;

	NSURLConnection *urlConnection;
    NSURLResponse *urlResponse;
	NSMutableData *urlData;
    URLCredential *urlCredential;
    URLDownloaderState state;
}

@property(retain) id <URLDownloaderDelegate> delegate;
@property(nonatomic, readonly) URLDownloaderState state;

+ (id)downloaderWithDelegate:(id)obj;
- (id)initWithDelegate:(id)obj;
- (BOOL)download:(NSURLRequest *)request withCredential:(URLCredential *)credential;
- (BOOL)cancel;
- (int)fullContentSize;
- (int)downloadedContentSize;
- (float)downloadCompleteProcent;
- (BOOL)isInProgress;

@end
