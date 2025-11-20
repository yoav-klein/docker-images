import io.micrometer.core.instrument.Gauge;
import io.micrometer.core.instrument.MeterRegistry;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.util.concurrent.atomic.AtomicInteger;

import io.micrometer.observation.Observation;
import io.micrometer.observation.ObservationHandler;
import org.springframework.http.client.observation.ClientRequestObservationContext;



@Configuration
public class Observability {

    @Bean
    Foo foo() { return new Foo(); }

    @Bean
    public AtomicInteger httpClientInFlightCounter(MeterRegistry registry) {
        AtomicInteger inFlight = new AtomicInteger(0);

        Gauge.builder("http.client.requests.in_flight", inFlight, AtomicInteger::get)
             .description("Number of in-flight HTTP client requests")
             .register(registry);
        
        System.out.println("httpClientInFlightCounter");

        return inFlight;
    }

    @Bean
    public ObservationHandler<ClientRequestObservationContext> clientInFlightHandler(
            AtomicInteger httpClientInFlightCounter) {

        return new ObservationHandler<>() {

            @Override
            public void onStart(ClientRequestObservationContext context) {
                httpClientInFlightCounter.incrementAndGet();

                System.out.println("clientInFlightHandler:: onStart");
            }

            @Override
            public void onStop(ClientRequestObservationContext context) {
                System.out.println("clientInFlightHandler:: onStop");
                httpClientInFlightCounter.decrementAndGet();
            }

            @Override
            public boolean supportsContext(Observation.Context context) {
                //return context instanceof ClientRequestObservationContext;
                return true;
            }
        };
    }
}
