package org.example;

import java.util.concurrent.atomic.AtomicInteger;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.http.client.observation.ClientRequestObservationContext;

import io.micrometer.core.instrument.Gauge;
import io.micrometer.core.instrument.MeterRegistry;
import io.micrometer.observation.Observation;
import io.micrometer.observation.ObservationHandler;
@Configuration
public class Observability {

    @Bean
    public AtomicInteger httpClientInFlightCounter(MeterRegistry registry) {
        AtomicInteger inFlight = new AtomicInteger(0);

        Gauge.builder("http.client.requests.in_flight", inFlight, AtomicInteger::get)
             .description("Number of in-flight HTTP client requests")
             .register(registry);

        return inFlight;
    }

    @Bean
    public ObservationHandler<ClientRequestObservationContext> clientInFlightHandler(
            AtomicInteger httpClientInFlightCounter) {

        return new ObservationHandler<>() {

            @Override
            public void onStart(ClientRequestObservationContext context) {
                httpClientInFlightCounter.incrementAndGet();
            }

            @Override
            public void onStop(ClientRequestObservationContext context) {
                httpClientInFlightCounter.decrementAndGet();
            }

            @Override
            public boolean supportsContext(Observation.Context context) {
                return context instanceof ClientRequestObservationContext;
                
            }
        };
    }
}
